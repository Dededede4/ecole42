#!/usr/bin/env node

const torrentStream = require('torrent-stream');
const fs = require('fs');
const Transcoder = require('stream-transcoder');
const amqp = require('amqplib');
const request = require('request-promise');

var Peer = require('simple-peer');

const movieExtensions = ['mp4', 'mkv', 'avi'];
const otherExtension = ['srt'];

const secret_key = 'toto';

const TEST_MOD = false;

const URL = 'amqp://localhost';

const API_URL = 'http://localhost';

const OTHER_DIR = '/var/www/public/download/other/';

const send_file_name = ({ btih, names }) =>
  request({
    method: 'POST',
    json: true,
    body: { names },
    uri: `${API_URL}/video/${btih}/add/subtitle`,
    headers: { token: secret_key },
  });

const send_file_size = ({ btih, length }) =>
  request({
    method: 'POST',
    json: true,
    body: { length },
    uri: `${API_URL}/video/${btih}/set/size`,
    headers: { token: secret_key },
  });

const send_size_downloaded = ({ btih, length }) =>
  request({
    method: 'POST',
    json: true,
    body: { length },
    uri: `${API_URL}/video/${btih}/add/size`,
    headers: { token: secret_key },
  });


const started = (engine, btih = 'test') => () => {
  let lock = false;
  let files_list = [];
  const files = engine.files.filter(
    file =>
      movieExtensions.includes(file.name.split('.').pop()) ||
      otherExtension.includes(file.name.split('.').pop())
  );
  files.forEach(file => {
    if (otherExtension.includes(file.name.split('.').pop())) {
      if (!fs.existsSync(`${OTHER_DIR}/${btih}`)) {
        fs.mkdirSync(`${OTHER_DIR}/${btih}`);
      }
      files_list.push(file.name);
      return file
        .createReadStream()
        .pipe(fs.createWriteStream(`${OTHER_DIR}/${btih}/${file.name}`));
    }
    if (lock) return; // download only one video file
    send_file_size({ btih, length: file.length });
    lock = true;
    const stream = file.createReadStream();
    var downloaded = 0;
    stream.on('data', function(chunk){
      downloaded += chunk.length;
      send_size_downloaded({ btih, length: downloaded });
    })
 
    new Transcoder(stream)
      .maxSize(320, 240)
      .videoCodec('h264')
      .videoBitrate(800 * 1000)
      .fps(25)
      .audioCodec('aac')
      .sampleRate(44100)
      .channels(2)
      .audioBitrate(128 * 1000)
      .format('mp4')
      .on('finish', function() {
        next();
      })
      .stream()
      .pipe(fs.createWriteStream(`/var/www/public/download/stream/${btih}.mp4`));
  });
  send_file_name({ btih, names: files_list });
};

const consumer = async msg => {
  let engine;
  if (TEST_MOD) {
    engine = torrentStream(
      'magnet:?xt=urn:btih:284894b9787ee116983ea738742923d9a0ca1d5d&dn=Robin.Hood.2018.HC.HDRip.XviD.AC3-EVO&tr=udp%3A%2F%2Ftracker.leechers-paradise.org%3A6969&tr=udp%3A%2F%2Fzer0day.ch%3A1337&tr=udp%3A%2F%2Fopen.demonii.com%3A1337&tr=udp%3A%2F%2Ftracker.coppersurfer.tk%3A6969&tr=udp%3A%2F%2Fexodus.desync.com%3A6969'
    );
    engine.on('ready', started(engine));
  } else {
    const btih = msg.content.toString();
    console.log(` [x] Received ${btih}`);
    engine = torrentStream(fs.readFileSync(`/var/www/public/download/torrent/${btih}.torrent`));
    engine.on('ready', started(engine, btih));
  }
};

const main = async () => {
  const ch = await amqp.connect(URL).then(con => con.createChannel());
  const q = 'torrent-to-download';
  ch.assertQueue(q, { durable: true });
  console.log(` [*] Waiting for messages in ${q}. To exit press CTRL+C`);
  ch.consume(q, consumer);
};

if (TEST_MOD) consumer();
else main();

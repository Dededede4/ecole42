import React from 'react';
import Stars from '../components/stars';
import langue from '../modules/langage';
import movies from './movies';

const video = {
  title: 'Rabbit',
  productor: 'egg',
  actor: 'the white rabbit',
  date: '2018',
  duration: '1h30',
  rate: 4,
  description: 'Ad vitam aeternm blablabla patati patatat...',
};

const noData = 'http://www.aesvt-maroc.com/wp-content/uploads/2016/09/profil.jpg';

const DescriptionComponent = ({ video }) => (
  <article className="box" style={{ width: '100%', position: 'relative' }}>
    <div className="columns">
      <div className="column">
        {langue.translate('productor') + ':'}
        <p className="subtitle">
          <b>{video.productor}</b>
        </p>
        {langue.translate('actor') + ':'}
        <p className="subtitle">
          <b>{video.actor}</b>
        </p>
        {langue.translate('date') + ':'}
        <p className="subtitle">
          <b>{video.date}</b>
        </p>
      </div>
      <div className="column">
        {langue.translate('duration') + ':'}
        <p className="subtitle">
          <b>{video.duration}</b>
        </p>
        {langue.translate('description') + ':'}
        <p className="subtitle">
          <b>{video.description}</b>
        </p>
        {langue.translate('rate') + ':'}
        <p className="subtitle">
          <b>
            <Stars rate={video.rate} onClick={console.log} />
          </b>
        </p>
      </div>
    </div>
  </article>
);

const comments = [
  {
    text: 'Not bad ar all',
    username: 'tet',
  },
  {
    text:
      "Armstrong was really something. I didn't especially like the film but I benefitted from the experience of becoming more familiar withe life of this extraordinary man.",
    username: 'tet',
  },
  {
    text: 'Tired of regular P..0..R..N? Come to us-> D A T X X X . C O M',
    username: 'tet',
  },
  {
    text:
      'eskeptical people will always say "the earth is flat" and that humanity never landed on the moon .',
    username: 'tet',
  },
  {
    text: 'Better than Apollo 13',
    username: 'tet',
  },
  {
    text: 'AWESOME',
    username: 'tet',
  },
  {
    text: 'How can I download videos from hate...???',
    username: 'tet',
  },
];

const MoviePage = ({ match }) => (
  <div>
    <h1 className="title is-2" style={{ textAlign: 'center' }}>
      {video.title}
    </h1>
    <video height="640" with="360" style={{ display: 'block', margin: '0 auto' }} controls>
      <source src="http://clips.vorwaerts-gmbh.de/VfE_html5.mp4" type="video/mp4" />
    </video>
    <hr />
    <DescriptionComponent video={video} />
    <hr />
    <h1 className="title is-4" style={{ textAlign: 'center' }}>
      Comments
    </h1>
    <textarea className="textarea" placeholder="Your comment" />
    <button className="button is-info" style={{ float: 'right', marginTop: '1em' }}>
      Comment !
    </button>
    <div style={{ marginTop: '5em' }}>
      {comments.map((comment, index) => (
        <div key={index} style={{ margin: '1em' }} className="card">
          <div className="card-content" style={{ display: 'flex' }}>
            <span>
              <h1
                className="title is-6"
                style={{ textAlign: 'center', marginTop: '-0.7em', marginBottom: '-0.01em' }}
              >
                {comment.username}
              </h1>
              <img
                src={comment.userpic || noData}
                style={{ width: '50px', height: '50px' }}
                className="profilPicture"
              />
            </span>
            <h1 style={{ marginLeft: '1em' }}>{comment.text}</h1>
          </div>
        </div>
      ))}
    </div>
  </div>
);

export default MoviePage;

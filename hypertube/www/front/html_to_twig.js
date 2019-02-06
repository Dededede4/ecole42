const fs = require('fs');

function read(fileName, type) {
  return new Promise(function(resolve, reject) {
    fs.readFile(fileName, type, (err, data) => {
      err ? reject(err) : resolve(data);
    });
  });
}

function write(fileName, data) {
  return new Promise(function(resolve, reject) {
    fs.writeFile(fileName, data, (err, data) => {
      err ? reject(err) : resolve(data);
    });
  });
}

const replace_src = (_, p1) => `src="{{ asset('react/${p1}')}}"`;
const replace_linkhref = (_, p1) => `link href="{{ asset('react/${p1}')}}"`;

const main = async () => {
  if (process.argv.length <= 2)
    return console.error('Usage: node script.js [SOURCE] [DESTINATION(OPTIONNAL)]');
  const source = process.argv[2];
  const dest = process.argv.length === 3 ? null : process.argv[3];
  const file = (await read(source, 'utf8'))
    .replace(
      `<link rel="shortcut icon" href="/favicon.ico"/>`,
      `<link rel="shortcut icon" href="{{ asset('favicon.ico') }}" />`
    )
    .replace(
      `<link rel="manifest" href="/manifest.json"/>`,
      `<link rel="manifest" href="{{ asset('manifest.json') }}" />`
    )
    .replace(
      `<title>React App</title>`,
      `<title>{% block title %}Welcome!{% endblock %}</title>\n{% block stylesheets %}{% endblock %}`
    )
    .replace(`<div id="root">`, `{% block body %}<div id="root"></div>{% endblock %}`)
    .replace(`</div><script>`, `<script>{% block javascripts %}`)
    .replace(`</script></body>`, `</script>{% endblock %}\n</body>`)
    .replace(/src="(.*?)"/g, replace_src)
    .replace(/link href="(.*?)"/g, replace_linkhref)
    ;
  if (!dest) return console.log(file);
  const res = await write(dest, file).catch(e => true);
  if (!!res) console.error('Failure');
  else console.log('Sucess');
};

main();

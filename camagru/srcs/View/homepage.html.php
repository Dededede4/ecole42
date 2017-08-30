<!-- Coucou mes <a href="<?= $this->path('is_my_name_ah', array('LOL')) ?>">cocos</a> :) -->
    <!doctype html>
    <html>
    <head>
        <meta charset="UTF-8">
        <title><!-- --></title>
        <style>
            html {
                margin:0;
                padding:0;
                background: url(img/bgblack.jpg) no-repeat center fixed;
                background-size: cover;

                overflow: hidden;

                font-family:  -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, "Helvetica Neue", Arial, sans-serif;
            }

            h1 {
                color: #fff;
                margin-left:100px;
                margin-top:50px;
            }
        </style>
    </head>
    <body>

    <div id="jsGeneric">
        <h1>Le projet Camagru n'est pas qu'un projet.</h1>
        <h1>C'est une histoire entre un dev et son framework.</h1>
        <h1>Une histoire entre un corrigé et son correcteur.</h1>
        <h1>C'est une plateforme simple, rapide et efficace.</h1>
        <h1>Une plateforme pour vos photos.</h1>
        <h1>Une plateforme pour vos souvenirs.</h1>
        <h1>Une plateforme pour vous.</h1>
        <h1>Vous permettre de voir le monde.</h1>
        <h1>Permettre au monde de vous voir.</h1>
        <h1>Ne ratez plus rien.</h1>
        <h1>Plus rien ne sera jamais pareil.</h1>
    </div>

    <script>
        var mainblock = document.getElementById('jsGeneric');
        function pop() {
            mainblock.style.opacity = 0;
            mainblock.style.marginTop = '0px';
            var i = 0;
            var stop = setInterval(function () {
                i  += 0.1;
                mainblock.style.opacity = i;
                if (i >= 1)
                {
                    clearInterval(stop);
                    defil();
                    return;
                }
            }, 50);
        }

        function defil() {
            setTimeout(function () {
                var i = 0;
                var stop = setInterval(function () {
                    console.log(i);
                    if (i === -1000) {
                        clearInterval(stop);
                        pop();
                        return;
                    }
                    i--;
                    mainblock.style.marginTop = i + 'px';
                }, 50);
            }, 1000)
        }
        defil();
    </script>
    </body>
</html>

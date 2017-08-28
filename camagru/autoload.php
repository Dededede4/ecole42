<?php

spl_autoload_register(function ($class) {
    $pathFramework = str_replace('\\', '/', $class).'.php';
    $pathSrcs = ROOTDIR.'/srcs/'.$pathFramework;

    if (file_exists($pathSrcs)) {
        require_once $pathSrcs;
    } else {
        require_once $pathFramework;
    }
});

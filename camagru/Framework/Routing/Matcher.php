<?php

namespace Framework\Routing;

use Framework\Http\Request;

class Matcher
{
    public static function isMatch($path, Request $request)
    {
        $requestArguments = explode('/', $request->getPathInfo());
        $pathArguments = explode('/', $path);

        if (count($requestArguments) != count($pathArguments)) {
            return false;
        }
        $stop = count($requestArguments);
        for ($i = 0; $i < $stop; $i++) {
            if (!empty($pathArguments[$i]) && $pathArguments[$i][0] === '{' && substr($pathArguments[$i], -1) === '}') {
                continue;
            }
            if ($pathArguments[$i] === $requestArguments[$i]) {
                continue;
            }

            return false;
        }

        return true;
    }

    public static function extract($path, Request $request, $args = array())
    {
        $requestArguments = explode('/', $request->getPathInfo());
        $pathArguments = explode('/', $path);

        if (count($requestArguments) != count($pathArguments)) {
            return;
        }
        $stop = count($requestArguments);
        for ($i = 0; $i < $stop; $i++) {
            if (!empty($pathArguments[$i]) && $pathArguments[$i][0] === '{' && substr($pathArguments[$i], -1) === '}') {
                $args[] = $requestArguments[$i];
                continue;
            }
            if ($pathArguments[$i] === $requestArguments[$i]) {
                continue;
            }

            return;
        }

        return $args;
    }

    public static function insert($path, $args = array())
    {
        $urlArray = array();
        $i = 0;
        $pathArguments = explode('/', $path);

        foreach ($pathArguments as $argument) {
            if (!empty($argument) && $argument[0] === '{' && substr($argument, -1) === '}') {
                $urlArray[] = $args[$i++];
            } else {
                $urlArray[] = $argument;
            }
        }

        return implode('/', $urlArray);
    }
}
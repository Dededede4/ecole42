<?php

namespace framework\http;

class Request implements RequestInterface
{
    public function getPathInfo()
    {
        return $_SERVER['PATH_INFO'] ?? '/';
    }
}
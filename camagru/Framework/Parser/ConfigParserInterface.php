<?php

namespace Framework\Parser;


interface ConfigParserInterface
{
    public function setPath($path);

    public function getConfig();
}
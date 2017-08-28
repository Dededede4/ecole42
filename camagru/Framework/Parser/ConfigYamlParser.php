<?php

namespace Framework\Parser;

class ConfigYamlParser implements ConfigParserInterface
{
    public function getConfig($path)
    {
        // TODO: Implement getConfig() method.

        var_dump(\yaml_parse(file_get_contents($path)));
    }
}
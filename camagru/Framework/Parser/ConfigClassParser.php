<?php

namespace Framework\Parser;

class ConfigClassParser implements ConfigParserInterface
{
    private $path;

    public function setPath($path)
    {
        $this->path = $path;
    }

    public function getConfig()
    {
        return $this->parseClass($this->path);
    }

    public function parseClass($class)
    {
        $rc = new \ReflectionClass($class);
        $methods = $rc->getMethods(\ReflectionMethod::IS_PUBLIC);
        $config = array();
        foreach ($methods as $method) {
            $config[] = $this->parseMethod($method);
        }

        return $config;
    }

    public function parseMethod(\ReflectionMethod $rm)
    {
        return array(
            'controller' => $rm->class.':'.$rm->name,
            'params' => $this->parseText($rm->getDocComment())
        );
    }

    public function parseText($text)
    {
        $lines = explode("\n", $text);
        $config = array();

        foreach ($lines as $line) {
            if (empty($line) || 0 !== substr_compare(ltrim($line), '* @', 0, 3)) {
                continue;
            }
            $instruct = strchr($line, '@');
            $instruct = substr($instruct, 1);
            $row = explode(' ', $instruct);
            $configName = array_shift($row);
            $config[$configName] = $row;
        }

        return $config;
    }
}
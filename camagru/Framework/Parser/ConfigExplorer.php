<?php

namespace Framework\Parser;

use Framework\Tool\MagicMethodTrait;

class ConfigExplorer
{

    use MagicMethodTrait;

    private $lines;

    private $ilines;

    public function load(ConfigParserInterface $c)
    {
        $this->lines = $c->getConfig();
        $this->ilines = array_change_key_case($this->lines, CASE_LOWER);

        $this->setAuthorizedMagicMethods(array('findAll'));
    }

    public function findAll($name)
    {
        $entries = array();
        $name = strtolower($name);

        foreach ($this->ilines as $line) {
            if (isset($line[$name])) {
                $entries[] = $line[$name];
            }
        }

        return $entries;
    }
}
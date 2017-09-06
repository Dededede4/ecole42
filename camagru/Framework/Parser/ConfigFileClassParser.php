<?php

namespace Framework\Parser;

class ConfigFileClassParser extends ConfigClassParser
{
    public function setPath($folder, $fileSuffix = false, $namespace = '')
    {
        $globalconfig = array();
        $files = scandir($folder);
        foreach ($files as $file) {
            if (!$fileSuffix || false !== strpos($file, $fileSuffix)) {
                $className = strchr($file, '.', true);
                $class = $namespace.$className;
                $rc = new \ReflectionClass($class);
                $propri = $rc->getProperties(); // ça à dynamiser
                $results = array();
                foreach ($propri as $p) {
                    $results[$p->name] = $this->parseText($p->getDocComment());
                }
                $globalconfig[] = array(
                    'class' => $class,
                    'fileconfig' => $this->parseText($rc->getDocComment()),
                    'results' => $results,
                );
            }
        }

        return $globalconfig;
    }
}
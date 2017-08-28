<?php

namespace Framework\Container;

class Container
{
    private $values;

    public function __construct(array $values)
    {
        $this->values = $values;
    }

    public function get($key)
    {
        return $this->values[$key];
    }

    public function set($key, $value)
    {
        $this->values[$key] = $value;
    }
}
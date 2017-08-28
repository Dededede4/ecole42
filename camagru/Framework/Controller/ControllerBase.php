<?php

namespace Framework\Controller;

use Framework\Http\Response;


abstract class ControllerBase
{
    private $container;

    public function setContainer($container)
    {
        $this->container = $container;
    }

    public function get($name)
    {
        return $this->container->get($name);
    }

    public function render($path, array $vars = array())
    {
        $engine = $this->get('engine');

        return new Response($engine->render($path, $vars));
    }
}
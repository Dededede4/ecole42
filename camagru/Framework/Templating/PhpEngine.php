<?php

namespace Framework\Templating;

use Framework\Routing\Resolver;

class PhpEngine
{
    private $resolver;

    public function __construct(Resolver $resolver)
    {
        $this->resolver = $resolver;
    }

    public function path($routeName, $args = array())
    {
        return $this->resolver->generatePath($routeName, $args);
    }

    public function render($path, array $vars = array())
    {
        ob_start();
        include(ROOTDIR.'/srcs/View/'.$path);
        $html = ob_get_contents();
        ob_end_clean();

        return $html;
    }
}
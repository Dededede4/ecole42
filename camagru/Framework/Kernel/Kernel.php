<?php

namespace Framework\Kernel;

use Framework\Container\Container;
use Framework\Http\RequestInterface;
use Framework\Parser\ConfigExplorer;
use Framework\Routing\Resolver;
use Framework\Parser\ConfigClassParser;
use Framework\Parser\ConfigFileClassParser;
use Framework\Templating\PhpEngine;
use Framework\ORM\EntityManager;

class Kernel
{
    private $container;

    private $request;

    public function getResponse(RequestInterface $request)
    {
        $container = new Container(
            array(
                'request' => $request,
                'config_parser' => new ConfigClassParser(),
            )
        );

        $container->set('config_explorer', new ConfigExplorer());
        $container->set('resolver', new Resolver($container->get('config_explorer'), $container->get('config_parser'), $container));
        $container->set('engine', new PhpEngine($container->get('resolver'), $request));
        $container->set('entity_manager', new EntityManager(new ConfigFileClassParser()));

        $container->get('entity_manager')->schemaUpdate();

        $this->container = $container;

        return $this->get('resolver')->executeController($request);
    }

    public function get($name)
    {
        return $this->getContainer()->get($name);
    }

    public function getContainer()
    {
        return $this->container;
    }

    public function getRequest()
    {
        return $this->request;
    }
}
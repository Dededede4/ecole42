<?php

namespace Framework\Routing;

use Framework\Http\RequestInterface;
use Framework\Parser\ConfigExplorer;
use Framework\Parser\ConfigParserInterface;
use Framework\Routing\Matcher;
use Framework\Controller\ControllerBase;
use Framework\Container\Container;

class Resolver
{
    private $explorer;

    private $parser;

    public function __construct(ConfigExplorer $explorer, ConfigParserInterface $parser, Container $container)
    {
        $this->explorer = $explorer;
        $this->parser = $parser;
        $this->container = $container;
    }

    public function executeController(RequestInterface $request)
    {
        $parser = $this->parser;
        $explorer = $this->explorer;
        $files = scandir(ROOTDIR.'/srcs/Controller');
        foreach ($files as $file) {
            if (false !== strpos($file, 'Controller')) {
                $controller = strchr($file, '.', true);
                $controllerClass = 'Controller\\'.$controller;
                $parser->setPath($controllerClass);
                $config = $parser->getConfig();
                foreach ($config as $controllerConfig) {
                    if (!isset($controllerConfig['params']['path'])) {
                        continue;
                    }

                    if (Matcher::isMatch($controllerConfig['params']['path'][0], $request)) {
                        $controllerName = explode(':', $controllerConfig['controller']);
                        $controllerClass = $controllerName[0];
                        $controllerMethod = $controllerName[1];
                        $controller = new $controllerClass();

                        if ($controller instanceof ControllerBase) {
                            $controller->setContainer($this->container);
                        }

                        $args = Matcher::extract($controllerConfig['params']['path'][0], $request, array($request));
                        $returnValue = call_user_func_array(array($controller, $controllerMethod), $args);
                        if (!($returnValue instanceof \Framework\Http\ResponseInterface)) {
                            throw new \Exception('Controller not return ResponseInterface object');
                        }

                        return $returnValue;
                    }
                }
                $explorer->load($parser);
            }
        }

        throw new \Exception('404 Error');
    }

    public function generatePath($routeName, $params = array())
    {
        // TODO : DRY !!
        $parser = $this->parser;
        $explorer = $this->explorer;
        $files = scandir(ROOTDIR.'/srcs/Controller');
        foreach ($files as $file) {
            if (false !== strpos($file, 'Controller')) {
                $controller = strchr($file, '.', true);
                $controllerClass = 'Controller\\'.$controller;
                $parser->setPath($controllerClass);
                $config = $parser->getConfig();
                foreach ($config as $controllerConfig) {
                    if (!isset($controllerConfig['params']['path'])) {
                        continue;
                    }

                    // ENDTODO
                    if ($routeName === $controllerConfig['params']['name'][0]) {
                        return Matcher::insert($controllerConfig['params']['path'][0], $params);
                    }
                }
                $explorer->load($parser);
            }
        }

        throw new \Exception('Route no found');
    }
}
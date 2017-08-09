<?php
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);


use Symfony\Component\EventDispatcher\EventDispatcher;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\HttpFoundation\RequestStack;
use Symfony\Component\HttpFoundation\Response;
use Symfony\Component\HttpKernel\Controller\ArgumentResolver;
use Symfony\Component\HttpKernel\Controller\ControllerResolver;
use Symfony\Component\HttpKernel\EventListener\RouterListener;
use Symfony\Component\HttpKernel\HttpKernel;
use Symfony\Component\Routing\Matcher\UrlMatcher;
use Symfony\Component\Routing\RequestContext;
use Symfony\Component\Routing\Route;
use Symfony\Component\Routing\RouteCollection;


require "vendor/autoload.php";
/*
$iterator = new LimitIterator(
    new InfiniteIterator(
        new ArrayIterator(range(1, 3))
    ),
    0,
    9
);

echo implode(', ', iterator_to_array($iterator));
exit(0);*/

$routes = new RouteCollection();
$routes->add('hello', new Route('/hello/{name}', array(
    '_controller' => function (Request $request) {
        return new Response(
            sprintf("Hello %s", $request->get('name'))
        );
    }, 'name' => 'toto'
    	),
array('name' => '[0-9]{4}-[0-9]{2}')
));

$request = Request::createFromGlobals();

$matcher = new UrlMatcher($routes, new RequestContext());

$dispatcher = new EventDispatcher();
$dispatcher->addSubscriber(new RouterListener($matcher, new RequestStack()));

$controllerResolver = new ControllerResolver();
$argumentResolver = new ArgumentResolver();

$kernel = new HttpKernel($dispatcher, $controllerResolver, new RequestStack(), $argumentResolver);

$response = $kernel->handle($request);
$response->send();


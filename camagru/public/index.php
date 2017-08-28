<?php
error_reporting(E_ALL);
ini_set('display_errors', 1);

use Framework\Http\Request;
use Framework\Kernel\Kernel;

CONST ROOTDIR = '..';

require_once ROOTDIR.'/autoload.php';

$kernel = new Kernel();
$response = $kernel->getResponse(new Request());

$response->send();
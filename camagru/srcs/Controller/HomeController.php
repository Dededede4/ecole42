<?php

namespace Controller;

use Framework\Controller\ControllerBase;
use Framework\Http\Request;

class HomeController extends ControllerBase
{
    /**
     * @path /
     * @name hello
     */
    public function test1Action()
    {
        return $this->render('homepage.html.php');
    }

    /**
     * @path /name/{name}
     * @name is_my_name
     */
    public function test2Action(Request $request, $name)
    {
        $url = $this->get('resolver')->generatePath('is_my_name_ah', array('coucou bg'));
    }

    /**
     * @path /name/{name}/truc
     * @name is_my_name_ah
     */
    public function test3Action(Request $request, $name)
    {
        echo 'ah !';
        var_dump($name);
        die;
    }
}
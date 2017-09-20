<?php

namespace Controller;

use Framework\Controller\ControllerBase;
use Framework\Form\Form;
use Framework\Form\TextType;
use Framework\Http\Request;

class UserController extends ControllerBase
{
    /**
     * @path /login
     * @name login
     */
    public function loginAction()
    {
        $form = new Form();
        $form->addChild(new TextType('username'));

        return $this->render('user/login.html.php', array('form' => $form));
    }
}

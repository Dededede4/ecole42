<?php

namespace Framework\Form;

class Form
{
    private $method;

    private $action;

    private $childs = array();

    public function __construct()
    {
        $this
            ->setMethod('POST')
            ->setAction('#');
    }

    public function renderStart($args = array())
    {
        return '<form method="'.$this->method.'" action="'.$this->action.'">';
    }

    public function render()
    {
        $str = $this->renderStart();
        foreach ($this->childs as $child)
        {
            $str .= $child->render();
        }
        $str .= $this->renderEnd();
        return $str;
    }

    public function renderEnd()
    {
        return '</form>';
    }

    /**
     * @param mixed $method
     */
    public function setMethod($method)
    {
        $this->method = $method;

        return $this;
    }

    /**
     * @param mixed $action
     */
    public function setAction($action)
    {
        $this->action = $action;

        return $this;
    }

    /**
     * @param mixed $child
     */
    public function addChild($child)
    {
        $this->childs[] = $child;

        return $this;
    }
}
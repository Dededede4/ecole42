<?php

namespace Framework\Form;

class TextType
{
    private $value;

    private $name;

    public function __construct($name, $value = '')
    {
        $this->name = $name;
        $this->value = $value;
    }

    public function renderStart($args = array())
    {
        $rest = '';
        if (!empty($this->value))
        {
            $rest = ' value="'.$this->value.'"';
        }
        $label = '';
        if(!empty($args['label']))
        {
            $label = '<label for="form_'.$this->name.'">'.$args['label'].'</label>';
        }
        return $label.'<input type="text" id="form_'.$this->name.'" name="'.$this->name.'"'.$rest.'>';
    }

    public function render()
    {
        return $this->renderStart();
    }

    public function renderEnd()
    {
        return '';
    }
}
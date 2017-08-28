<?php

namespace Framework\Http;

class Response implements ResponseInterface
{
    private $content;

    public function __construct($content)
    {
        $this->setContent($content);
    }

    public function setContent($content)
    {
        $this->content = $content;
    }

    public function getContent()
    {
        return $this->content;
    }

    public function send()
    {
        echo $this->getContent();
    }
}
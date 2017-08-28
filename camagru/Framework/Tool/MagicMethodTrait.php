<?php

namespace Framework\Tool;

trait MagicMethodTrait
{

    private $authorizedMagicMethods = array();

    protected function setAuthorizedMagicMethods(array $tab)
    {
        $this->authorizedMagicMethods = $tab;
    }

    public function __call($name, $arguments)
    {
        foreach ($this->authorizedMagicMethods as $authorizedMethod) {
            if (empty($name) || 0 !== substr_compare($authorizedMethod, $name, 0, strlen($authorizedMethod))) {
                continue;
            }

            $firstArg = substr($name, strlen($authorizedMethod));
            array_unshift($arguments, $firstArg);

            return call_user_func_array(array($this, $authorizedMethod), $arguments);
        }

        throw new \Exception('Method "'.$name.'" is not implemented or not authorized in "'.__CLASS__.'".');
    }

}
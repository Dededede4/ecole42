<?php

class UnholyFactory{
	protected $fighters = array();

	public function absorb($obj){
		if ($obj instanceof Fighter)
		{
			if (!isset($this->fighters[$obj->type]))
			{
				echo '(Factory absorbed a fighter of type '.$obj->type.')'.PHP_EOL;
				$this->fighters[$obj->type] = $obj;
			}
			else
				echo '(Factory already absorbed a fighter of type '.$obj->type.')'.PHP_EOL;
			return $obj;
		}
		else
		{
			echo '(Factory can\'t absorb this, it\'s not a fighter)'.PHP_EOL;
		}
		return null;
	}

	public function fabricate($name)
	{
		if (isset($this->fighters[$name]))
		{
			echo '(Factory fabricates a fighter of type '.$name.')'.PHP_EOL;
			$ex = $this->fighters[$name];
			$class = get_class($ex);
			return new $class($name);
		}
		echo '(Factory hasn\'t absorbed any fighter of type '.$name.')'.PHP_EOL;
		return null;
	}
}
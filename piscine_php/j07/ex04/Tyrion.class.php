<?php
class Tyrion{
	public function sleepWith($p)
	{
		if ($p instanceof Jaime)
			echo 'Not even if I\'m drunk !'.PHP_EOL;
		if ($p instanceof Sansa)
			echo 'Let\'s do this.'.PHP_EOL;
		if ($p instanceof Cersei)
			echo 'Not even if I\'m drunk !'.PHP_EOL;
	}
}
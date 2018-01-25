<?php
class Jaime{
	public function sleepWith($p)
	{
		if ($p instanceof Cersei)
			echo 'With pleasure, but only in a tower in Winterfell, then.'.PHP_EOL;
		if ($p instanceof Sansa)
			echo 'Let\'s do this.'.PHP_EOL;
		if ($p instanceof Tyrion)
			echo 'Not even if I\'m drunk !'.PHP_EOL;
	}
}
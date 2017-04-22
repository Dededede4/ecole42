<?php

class NightsWatch
{
	private $fighters = array();

	public function recruit($fighter)
	{
		if ($fighter instanceof IFighter)
			$this->fighters[] = $fighter;
	}

	public function fight()
	{
		foreach ($this->fighters as $fighter) {
			$fighter->fight();
		}
	}
}
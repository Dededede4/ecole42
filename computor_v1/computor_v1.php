#!/Users/mprevot/.brew/bin/php 
<?php

function ft_sqrt(string $str): float
{
	echo "Coucou\n";

	$parts = explode('.', $str);
	if (count($parts) != 2)
		throw new \Error("Syntax error");
	$left = $parts[0];
	$right = $parts[1];

	
	var_dump($left);
	return 42.0;
}

function resolve(array &$left, array &$right)
{

}


class Member
{
	public $tokens;

	public function __construct(string $memberStr)
	{
		$this->tokens = explode(' ', $memberStr);
		if (!in_array($this->tokens[0], ['-', '+', '*', '/']))
		{
			array_unshift($this->tokens, '+');
		}
	}

	public function removeUselessTokens()
	{
		$len = count($this->tokens);
		for ($i=0; $i < $len; $i++) {
			// Remplace par 0 ['Y', '*', '0']
			// Remplace par 0 ['0', '*', 'Y']
			if ((in_array($this->tokens[$i], ['*', '/']) && '0' === $this->tokens[$i + 1])|| ($i > 1 && in_array($this->tokens[$i], ['*', '/']) && '0' === $this->tokens[$i - 1]))
			{
				$this->tokens[$i - 1] = '0';
				unset($this->tokens[$i]);
				unset($this->tokens[$i + 1]);
				$this->tokens = array_values($this->tokens);
				$this->removeUselessTokens();
				
				return;
			}
		}
		for ($i=0; $i < $len; $i++) {
			if (in_array($this->tokens[$i], ['-', '+']) && '0' === $this->tokens[$i + 1])
			{
				unset($this->tokens[$i]);
				unset($this->tokens[$i + 1]);
				$this->tokens = array_values($this->tokens);
				$this->removeUselessTokens();
				
				return;
			}
			if ('^0' === substr($this->tokens[$i], -2))
			{
				$this->tokens[$i] = '0';
				$this->removeUselessTokens();
				return;
			}
			if ('^1' === substr($this->tokens[$i], -2))
			{
				$this->tokens[$i] = substr($this->tokens[$i], 0, -2);
				$this->removeUselessTokens();
				return;
			}
		}
	}


	// Fusionne les tokens
	public function fusion()
	{
		$len = count($this->tokens);
		$first = null;
		$firstPos = 0;
		for ($i=0; $i < $len; $i++) {
			if (in_array($this->tokens[$i], ['+', '-'])
				&& $this->tokens[$i + 1] != 'X')
			{
				if ('+' === $this->tokens[$i])
				{
					$first = $this->tokens[$i + 1];
				}
				else
				{
					$first = 0 - $this->tokens[$i + 1];
				}
				$firstPos = $i;
				break;
			}
		}

		$second = null;
		for ($i=$i; $i < $len; $i++) {
			if (in_array($this->tokens[$i], ['+', '-'])
				&& $this->tokens[$i + 1] != 'X')
			{
				if ('+' === $this->tokens[$i])
				{
					$second = $this->tokens[$i + 1];
				}
				else
				{
					$second = 0 - $this->tokens[$i + 1];
				}
				$secondPos = $i;
				break;
			}
		}

		if (!is_null($first) && !is_null($second))
		{
			unset($this->tokens[$firstPos]);
			unset($this->tokens[$firstPos + 1]);
			unset($this->tokens[$secondPos]);
			unset($this->tokens[$secondPos + 1]);
			$this->tokens = array_values($this->$tokens);
			$result = $first + $second;
			if ($result > 0)
			{
				array_unshift($this->tokens, '+');
				array_unshift($this->tokens, $result);
			}
			if ($result < 0)
			{
				array_unshift($this->tokens, '-');
				array_unshift($this->tokens, 0 - $result);
			}
			
		}	

	}

	// On prends les tokens et on les places chez nous.
	// avant : 5 + 4 = 8 + 1
	// après : -1 - 8 + 5 + 4 = 0
	public function absorb(&$tokens)
	{
		if(0 === count($tokens))
			return ;

		$revertSigns = [
			'+' => '-',
			'-' => '+',
			'*' => '/',
			'/' => '*',
		];

		array_unshift($this->tokens, $tokens[1]);
		array_unshift($this->tokens, $revertSigns[$tokens[0]]);
		unset($tokens[0]);
		unset($tokens[1]);
		$tokens = array_values($tokens);
		$this->absorb($tokens);
	}
}


class Equation 
{
	public $member1;
	public $member2;

	public function __construct(string $equationStr)
	{
		$members = explode(' = ', $equationStr);
		$this->member1 = new Member($members[0]);
		$this->member2 = new Member($members[1]);
	}

	public function solve()
	{
		$this->member1->removeUselessTokens();
		$this->member2->removeUselessTokens();
		$this->member1->absorb($this->member2->tokens);
	}

	public function show()
	{
		if (0 === count($this->member1->tokens))
		{
			echo '0';
		}
		echo implode(' ', $this->member1->tokens) .' = '.implode(' ', $this->member2->tokens);
		if (0 === count($this->member2->tokens))
		{
			echo '0';
		}
	}
}



$arg = $argv[1];

echo 'OK on va résoudre "'.$arg.'"'."\n";

$equation = new Equation($arg);
//$equation->show();
echo "\n";
$equation->solve();
$equation->show();
echo "\n";


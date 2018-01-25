#!/usr/bin/php
<?php
if ($argc != 2)
	exit(0);
echo implode(' ', array_filter(explode(' ', $argv[1])))."\n";
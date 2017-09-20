<?php
$this->extends('base.html.php');

$this->startBlock(); ?>
    Bienvenue, connectez-vous !
    <?=$vars['form']->render()?>
<?php $this->endBlock("content");

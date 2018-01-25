<html>
	<head>
		<title>Achetez pauvres fou !</title>
		<style type="text/css">
			body{
				font-family: "Helvetica Neue",Helvetica,Arial,sans-serif;
				background-image: url("img/bg.gif");
			}
			.container{
				width: 80%;
				margin:auto;
			}
			.bgwhite{
				background-color:#FFF;
				padding: 25px;
				padding-top:20px;
				min-height: 90%;
				border-radius: 3px;
				border:1px solid #e5e5e5;
			}
			.logo{
				width: 100px;
			}
			.menu a{
				margin:50px;
				margin-right:5px;
				color:#67676d;
				text-decoration:none; 
			}
			.right{
				text-align: right;
			}
			.left{
				text-align: left;
			}
			.p100
			{
				width: 100%;
			}
			.flashmessage
			{
				width:80%;
				margin:auto;
				background-color: #dff0d8;
				color:#3c763d;
				border-color:#d6e9c6;
				padding: 10px;
				border-radius: 6px;
			}
		</style>
	</head>
	<body>
		<div class="container bgwhite">
			<div style="float:right;" class="menu">
				<?php
				if ($current_user && $current_user['is_admin'])
					echo '<a href="./?page=admin">Administration</a>';
				?>
				<a href="./?page=panier">Votre panier</a>
				<?php
				if(!$current_user)
				{ ?>
					<a href="./?page=connexion">Connexion</a>
					<a href="./?page=inscription">Inscription</a>
				<?php
				}
				else
				{
				?>
					<a href="./?page=archives">Vos archives</a>
					<a href="./?page=deconnexion">Déconnexion</a>
				<?php
				}
				?>
			</a>
			</div>
			<a href="./"><img src="img/logo.png" class="logo"></a><br/>
			<hr>
			<?php
				if (!empty($_SESSION['flashmessage']))
				{
					echo '<div class="flashmessage">'.$_SESSION['flashmessage'].'</div>';
					$_SESSION['flashmessage'] = '';
				}
			?>
			
			<?php include($view['path']); ?>
		</div>
	</body>
</html>
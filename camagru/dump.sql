SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

CREATE DATABASE IF NOT EXISTS `bde42` DEFAULT CHARACTER SET latin1 COLLATE latin1_swedish_ci;
USE `bde42`;

CREATE TABLE `archive_product` (
  `id` int(11) NOT NULL,
  `id_archive` int(11) NOT NULL,
  `id_product` int(11) NOT NULL,
  `price` int(11) NOT NULL,
  `quantity` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

INSERT INTO `archive_product` (`id`, `id_archive`, `id_product`, `price`, `quantity`) VALUES
(20, 11, 11, 2599, 1),
(21, 12, 11, 2599, 9);

CREATE TABLE `category` (
  `id` int(11) NOT NULL,
  `name` varchar(250) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

INSERT INTO `category` (`id`, `name`) VALUES
(1, 'Ã‰vÃ©nements'),
(2, 'VÃªtements'),
(3, 'Goodies'),
(4, 'Voyages'),
(5, 'Notre sÃ©lection');

CREATE TABLE `category_product` (
  `id_product` int(11) NOT NULL,
  `id_category` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

INSERT INTO `category_product` (`id_product`, `id_category`) VALUES
(1, 1),
(1, 4),
(13, 2),
(13, 3),
(3, 1),
(4, 4),
(7, 3),
(8, 3),
(9, 3),
(12, 2),
(12, 3),
(6, 3),
(10, 3),
(2, 1),
(2, 4),
(2, 5),
(5, 3),
(5, 5),
(11, 2),
(11, 5);

CREATE TABLE `product` (
  `id` int(11) NOT NULL,
  `name` varchar(255) NOT NULL,
  `price` int(11) NOT NULL,
  `picture` varchar(512) NOT NULL,
  `description` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

INSERT INTO `product` (`id`, `name`, `price`, `picture`, `description`) VALUES
(1, 'SoirÃ©e dÃ©sertique', 99999, 'img/products/event1.jpg', 'Rejoignez nous  pour la plus mÃ©morable soirÃ©e au pays des milles et une nuits !  Et si vous Ãªtes assez riche pour vous payez suffisamment de boissons a 15 euros, vous pouvez aussi vous perdre dans le dÃ©sert dâ€™Arabie !'),
(2, 'Ski Ã  la neige', 49999, 'img/products/event2.jpg', 'Prenez votre ticket a destination de Schtadt, dans les Alpes Suisse ! Luxation des genoux, fractures du crÃ¢ne et dÃ©boÃ®tement des Ã©paules garantie !'),
(3, 'Amusement Ã  la plage', 9999, 'img/products/event3.jpg', 'Venez Ã©clabousser un appareil photo hors de prix sur une petite plage de Bretagne ! Certes lâ€™eau est glacÃ© mais vous Ãªtes avec des copains!'),
(4, 'DÃ©part pour la jungle', 79999, 'img/products/event4.jpg', 'Voyagez jusque dans la pampa Ã©quatoriale, apprivoisez et ramenez votre animal prÃ©fÃ©rÃ©, au choix : araignÃ©es, serpent ou autre reptile des plus sympathiques !'),
(5, 'Mug 42', 2599, 'img/products/mug1.jpg', 'Mug de la sobriÃ©tÃ©, comporte des choses Ã©crites en trop petit pour pouvoir les lire.'),
(6, 'Mug You Know Nothing', 3099, 'img/products/mug2.jpg', 'Mug de lâ€™humilitÃ©, pour ceux et celles qui aiment se la pÃ©ter en sociÃ©tÃ©'),
(7, 'Mug Sexy', 3099, 'img/products/mug3.jpg', 'Mug pour ceux qui ont fail en piscine et qui cherchent des excuses.'),
(8, 'Sticker 42', 599, 'img/products/sticker1.jpg', 'LE sticker de lâ€™Ã©cole ! Soyez originaux et collez le sur votre ordi !'),
(9, 'Sticker 42 Red Edition', 999, 'img/products/sticker2.jpg', 'Sticker un peu moche mais qui change du logo que lâ€™on voit partout !'),
(10, 'Sticker Art 42', 999, 'img/products/sticker3.png', 'Parce que grÃ¢ce Ã  Art 42, on peut faire genre on est aussi calÃ© en art quâ€™en C'),
(11, 'Sweatshirt 42', 2599, 'img/products/sweat1.jpg', 'Sweatshirt de lâ€™Ã©cole! Si vous nâ€™aimez pas le logo nâ€™hÃ©sitez pas Ã  coller le sticker de lâ€™Ã©cole dessus !'),
(12, 'Tshirt 42', 1599, 'img/products/tshirt1.png', 'T-shirt de lâ€™Ã©cole! Avec la photo dâ€™un mec qui ressemble a Sadirac si on regarde en fermant bien les yeux.'),
(13, 'Tshirt Bodybuilder', 1998, 'img/products/tshirt2.jpg', 'T-shirt portÃ© par un mec qui ne fait clairement pas ses 15h de log / jour. Ne soyez pas comme lui, mais achetez quand mÃªme ce t-shirt.');

CREATE TABLE `user` (
  `id` int(11) NOT NULL,
  `username` varchar(255) NOT NULL,
  `password` varchar(129) NOT NULL,
  `address` text NOT NULL,
  `tel` varchar(128) NOT NULL,
  `is_admin` tinyint(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

INSERT INTO `user` (`id`, `username`, `password`, `address`, `tel`, `is_admin`) VALUES
(1, 'root', 'e0638d6406a1676a526930fc8bb93045e01f606e28f192418b24babe1e5cad3748f3a6846f2041028982dad161147a9eff1fb7c1cadb8683cfeabfb1f6ba47da', ' ', ' ', 1),
(10, 'Tim', '6fd9a6a608bb8c87bccfec26f73bce66b83599ca46483b0dbbb1396e2c2eeb12035f9d8224db10f67ce66bf1fcb4c89c1a77b1b6b9decc597c5493a0f45ec951', '', '', 0),
(11, 'toto', '7bfefd2b19af7ad8d4ff7b7801c601513685f883f45ec7cbacbf160367bfa5d218e4dea5634eaded4d90f3b8a1fd8a57d09d8173186c19ab791b96ece26624f6', '', '', 0),
(12, 'a', '4817a497557e0e7f3879ee7cfab9871d7b79d2d3c28daf75ff1e4e11f7c24c1f445b4007aa5473fc295858236e45e165827d4bcf1541f4e6ca15390157744b97', '', '', 0);

CREATE TABLE `user_archive` (
  `id` int(11) NOT NULL,
  `id_user` int(11) NOT NULL,
  `time` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=COMPACT;

INSERT INTO `user_archive` (`id`, `id_user`, `time`) VALUES
(11, 12, '2017-04-09 20:27:41'),
(12, 1, '2017-04-09 20:35:04');


ALTER TABLE `archive_product`
  ADD PRIMARY KEY (`id`);

ALTER TABLE `category`
  ADD PRIMARY KEY (`id`);

ALTER TABLE `product`
  ADD PRIMARY KEY (`id`);

ALTER TABLE `user`
  ADD PRIMARY KEY (`id`);

ALTER TABLE `user_archive`
  ADD PRIMARY KEY (`id`);


ALTER TABLE `archive_product`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=22;
ALTER TABLE `category`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=26;
ALTER TABLE `product`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=27;
ALTER TABLE `user`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=15;
ALTER TABLE `user_archive`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=13;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

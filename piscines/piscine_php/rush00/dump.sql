-- phpMyAdmin SQL Dump
-- version 4.6.0
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Apr 08, 2017 at 08:18 PM
-- Server version: 5.7.11
-- PHP Version: 7.0.0

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `bde42`
--

-- --------------------------------------------------------

--
-- Table structure for table `archive_product`
--

CREATE TABLE `archive_product` (
  `id` int(11) NOT NULL,
  `id_archive` int(11) NOT NULL,
  `id_product` int(11) NOT NULL,
  `price` int(11) NOT NULL,
  `quantity` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `archive_product`
--

INSERT INTO `archive_product` (`id`, `id_archive`, `id_product`, `price`, `quantity`) VALUES
(1, 2, 8, 6, 1),
(2, 3, 1, 1000, 9),
(3, 3, 2, 500, 9),
(4, 3, 3, 100, 1),
(5, 3, 7, 31, 5),
(6, 3, 9, 10, 1),
(7, 3, 8, 6, 1),
(8, 4, 1, 1000, 9),
(9, 4, 2, 500, 9),
(10, 4, 3, 100, 1),
(11, 4, 7, 31, 5),
(12, 4, 9, 10, 1),
(13, 4, 8, 6, 1),
(14, 5, 1, 1000, 5),
(15, 6, 1, 1000, 1),
(16, 7, 3, 100, 9);

-- --------------------------------------------------------

--
-- Table structure for table `category`
--

CREATE TABLE `category` (
  `id` int(11) NOT NULL,
  `name` varchar(250) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `category`
--

INSERT INTO `category` (`id`, `name`) VALUES
(1, 'Ã‰vÃ©nements'),
(2, 'VÃªtements'),
(3, 'Goodies'),
(4, 'Voyages');

-- --------------------------------------------------------

--
-- Table structure for table `category_product`
--

CREATE TABLE `category_product` (
  `id_product` int(11) NOT NULL,
  `id_category` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `category_product`
--

INSERT INTO `category_product` (`id_product`, `id_category`) VALUES
(16, 1),
(16, 2),
(16, 3),
(16, 4),
(20, 1),
(20, 2),
(20, 3),
(21, 1),
(21, 2),
(21, 3),
(22, 1),
(1, 1),
(1, 4),
(2, 1),
(2, 4),
(13, 2),
(13, 3),
(3, 1),
(4, 4),
(5, 3),
(6, 3),
(7, 3),
(8, 3),
(9, 3),
(10, 3),
(11, 2),
(12, 2),
(12, 3);

-- --------------------------------------------------------

--
-- Table structure for table `product`
--

CREATE TABLE `product` (
  `id` int(11) NOT NULL,
  `name` varchar(255) NOT NULL,
  `price` int(11) NOT NULL,
  `picture` varchar(512) NOT NULL,
  `description` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `product`
--

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
(13, 'Tshirt Bodybuilder', 1998, 'img/products/tshirt2.jpg', 'T-shirt portÃ© par un mec qui ne fait clairement pas ses 15h de log / jour. Ne soyez pas comme lui, mais achetez quand mÃªme ce t-shirt.'),
(14, 'TOUTESÂ LESÂ CATÃ‰GORIES', 98700, 'img/products', 'Incroyable.'),
(15, 'TOUTESÂ LESÂ CATÃ‰GORIES', 98700, 'img/products', 'Incroyable.'),
(16, 'TOUTESÂ LESÂ CATÃ‰GORIES', 98700, 'img/products', 'Incroyable.'),
(17, 'WTF', 99900, 'img/products', '999999'),
(18, '', 0, 'img/products', ''),
(19, 'soleil', 44400, 'img/products', '33333'),
(20, 'soleil', 44400, 'img/products', '33333'),
(21, 'soleil', 44400, 'img/products', '33333'),
(22, 'soleil', 44400, 'img/products', '33333');

-- --------------------------------------------------------

--
-- Table structure for table `user`
--

CREATE TABLE `user` (
  `id` int(11) NOT NULL,
  `username` varchar(255) NOT NULL,
  `password` varchar(129) NOT NULL,
  `address` text NOT NULL,
  `tel` varchar(128) NOT NULL,
  `is_admin` tinyint(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `user`
--

INSERT INTO `user` (`id`, `username`, `password`, `address`, `tel`, `is_admin`) VALUES
(1, 'root', 'e0638d6406a1676a526930fc8bb93045e01f606e28f192418b24babe1e5cad3748f3a6846f2041028982dad161147a9eff1fb7c1cadb8683cfeabfb1f6ba47da', '', '', 1);

-- --------------------------------------------------------

--
-- Table structure for table `user_archive`
--

CREATE TABLE `user_archive` (
  `id` int(11) NOT NULL,
  `id_user` int(11) NOT NULL,
  `time` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=COMPACT;

--
-- Dumping data for table `user_archive`
--

INSERT INTO `user_archive` (`id`, `id_user`, `time`) VALUES
(1, 1, '2017-04-08 20:40:47'),
(2, 1, '2017-04-08 20:41:17'),
(3, 1, '2017-04-08 20:41:33'),
(4, 1, '2017-04-08 20:42:10'),
(5, 1, '2017-04-08 21:03:41'),
(6, 1, '2017-04-08 21:49:31'),
(7, 1, '2017-04-08 21:49:50');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `archive_product`
--
ALTER TABLE `archive_product`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `category`
--
ALTER TABLE `category`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `product`
--
ALTER TABLE `product`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `user`
--
ALTER TABLE `user`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `user_archive`
--
ALTER TABLE `user_archive`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `archive_product`
--
ALTER TABLE `archive_product`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=17;
--
-- AUTO_INCREMENT for table `category`
--
ALTER TABLE `category`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=21;
--
-- AUTO_INCREMENT for table `product`
--
ALTER TABLE `product`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=23;
--
-- AUTO_INCREMENT for table `user`
--
ALTER TABLE `user`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;
--
-- AUTO_INCREMENT for table `user_archive`
--
ALTER TABLE `user_archive`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

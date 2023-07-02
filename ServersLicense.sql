-- phpMyAdmin SQL Dump
-- version 4.6.6deb5ubuntu0.5
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: 02 Iul 2023 la 20:34
-- Versiune server: 10.1.48-MariaDB-0ubuntu0.18.04.1
-- PHP Version: 7.2.34-38+ubuntu18.04.1+deb.sury.org+1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `DB`
--

-- --------------------------------------------------------

--
-- Structura de tabel pentru tabelul `ServersLicense`
--

CREATE TABLE `ServersLicense` (
  `uId` int(32) NOT NULL,
  `server_name` varchar(32) NOT NULL,
  `IpPort` varchar(32) NOT NULL,
  `Expires` varchar(20) NOT NULL,
  `discord_owner` varchar(32) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Salvarea datelor din tabel `ServersLicense`
--

--
-- Indexes for dumped tables
--

--
-- Indexes for table `ServersLicense`
--
ALTER TABLE `ServersLicense`
  ADD PRIMARY KEY (`uId`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `ServersLicense`
--
ALTER TABLE `ServersLicense`
  MODIFY `uId` int(32) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=12;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

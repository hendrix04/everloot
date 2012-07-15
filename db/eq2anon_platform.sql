-- phpMyAdmin SQL Dump
-- version 3.4.10.1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Jul 15, 2012 at 12:39 PM
-- Server version: 5.0.95
-- PHP Version: 5.2.6

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `eq2anon_platform`
--

-- --------------------------------------------------------

--
-- Table structure for table `difficultygroup`
--

CREATE TABLE IF NOT EXISTS `difficultygroup` (
  `difficultygroupid` bigint(20) unsigned NOT NULL auto_increment,
  `name` text NOT NULL,
  `color` varchar(6) NOT NULL,
  UNIQUE KEY `difficultygroupid` (`difficultygroupid`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=14 ;

-- --------------------------------------------------------

--
-- Table structure for table `grouplink`
--

CREATE TABLE IF NOT EXISTS `grouplink` (
  `grouplinkid` bigint(20) unsigned NOT NULL auto_increment,
  `toonid` bigint(20) NOT NULL,
  `toongroupid` bigint(20) NOT NULL,
  `userid` bigint(20) NOT NULL,
  PRIMARY KEY  (`grouplinkid`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=90 ;

-- --------------------------------------------------------

--
-- Table structure for table `loot`
--

CREATE TABLE IF NOT EXISTS `loot` (
  `lootid` bigint(20) unsigned NOT NULL auto_increment,
  `sonylootid` bigint(20) NOT NULL,
  `userid` bigint(20) NOT NULL,
  PRIMARY KEY  (`lootid`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=11 ;

-- --------------------------------------------------------

--
-- Table structure for table `lootdifficulty`
--

CREATE TABLE IF NOT EXISTS `lootdifficulty` (
  `lootdifficultyid` bigint(20) unsigned NOT NULL auto_increment,
  `sonylootid` bigint(20) NOT NULL,
  `difficultygroupid` bigint(20) NOT NULL,
  PRIMARY KEY  (`lootdifficultyid`),
  UNIQUE KEY `sonylootid` (`sonylootid`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=170 ;

-- --------------------------------------------------------

--
-- Table structure for table `serverlist`
--

CREATE TABLE IF NOT EXISTS `serverlist` (
  `serverlistid` bigint(20) unsigned NOT NULL auto_increment,
  `servername` text NOT NULL,
  `queryname` text NOT NULL,
  PRIMARY KEY  (`serverlistid`),
  UNIQUE KEY `serverlistid` (`serverlistid`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=17 ;

-- --------------------------------------------------------

--
-- Table structure for table `toon`
--

CREATE TABLE IF NOT EXISTS `toon` (
  `toonid` bigint(20) unsigned NOT NULL auto_increment,
  `sonytoonid` bigint(20) NOT NULL,
  `userid` bigint(20) NOT NULL,
  PRIMARY KEY  (`toonid`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=48 ;

-- --------------------------------------------------------

--
-- Table structure for table `toongroup`
--

CREATE TABLE IF NOT EXISTS `toongroup` (
  `toongroupid` bigint(20) unsigned NOT NULL auto_increment,
  `name` text NOT NULL,
  `userid` bigint(20) NOT NULL,
  PRIMARY KEY  (`toongroupid`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=20 ;

-- --------------------------------------------------------

--
-- Table structure for table `translation`
--

CREATE TABLE IF NOT EXISTS `translation` (
  `translationid` bigint(20) unsigned NOT NULL auto_increment,
  `sonytoonid` bigint(20) NOT NULL,
  `shortcode` text NOT NULL,
  PRIMARY KEY  (`translationid`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=17 ;

-- --------------------------------------------------------

--
-- Table structure for table `user`
--

CREATE TABLE IF NOT EXISTS `user` (
  `userid` bigint(20) unsigned NOT NULL auto_increment,
  `username` text NOT NULL,
  `password` text NOT NULL,
  `email` text NOT NULL,
  `adminyn` varchar(1) NOT NULL default 'N',
  PRIMARY KEY  (`userid`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=9 ;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

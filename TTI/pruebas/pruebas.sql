-- MySQL dump 10.16  Distrib 10.1.37-MariaDB, for debian-linux-gnueabihf (armv8l)
--
-- Host: localhost    Database: tt1Pruebas
-- ------------------------------------------------------
-- Server version	10.1.37-MariaDB-0+deb9u1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `posicion_servo`
--

DROP TABLE IF EXISTS `posicion_servo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `posicion_servo` (
  `posicion_x` int(11) DEFAULT NULL,
  `posicion_y` int(11) DEFAULT NULL,
  `mes` varchar(30) DEFAULT NULL,
  `estacion` varchar(30) DEFAULT NULL,
  `fecha_inicio` varchar(5) DEFAULT NULL,
  `fecha_fin` varchar(5) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `posicion_servo`
--

LOCK TABLES `posicion_servo` WRITE;
/*!40000 ALTER TABLE `posicion_servo` DISABLE KEYS */;
INSERT INTO `posicion_servo` VALUES (0,110,'Enero','Invierno','21-01','20-02'),(0,100,'Febrero','Invierno','21-02','20-03'),(0,90,'Marzo','Primavera','21-03','20-04'),(0,80,'Abril','Primavera','21-04','20-05'),(0,70,'Mayo','Primavera','21-05','20-06'),(0,70,'Junio','Verano','21-06','20-07'),(0,70,'Julio','Verano','21-07','20-08'),(0,80,'Agosto','Verano','21-08','20-09'),(0,90,'Septiembre','Otoño','21-09','20-10'),(0,100,'Octubre','Otoño','21-10','20-11'),(0,110,'Noviembre','Otoño','21-11','20-12'),(0,110,'Diciembre','Invierno','21-12','20-01');
/*!40000 ALTER TABLE `posicion_servo` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-02-05 17:14:03

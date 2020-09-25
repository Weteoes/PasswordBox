/*
 Navicat Premium Data Transfer

 Source Server         : .
 Source Server Type    : MySQL
 Source Server Version : 50726
 Source Host           : 127.0.0.1:3306
 Source Schema         : passwordbox

 Target Server Type    : MySQL
 Target Server Version : 50726
 File Encoding         : 65001

 Date: 25/09/2020 18:35:55
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for config
-- ----------------------------
DROP TABLE IF EXISTS `config`;
CREATE TABLE `config`  (
  `uid` varchar(255) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `config` text CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`uid`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = utf8 COLLATE = utf8_unicode_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for download
-- ----------------------------
DROP TABLE IF EXISTS `download`;
CREATE TABLE `download`  (
  `key` varchar(50) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `url` text CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`key`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = utf8 COLLATE = utf8_unicode_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for session
-- ----------------------------
DROP TABLE IF EXISTS `session`;
CREATE TABLE `session`  (
  `session` varchar(50) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `uid` varchar(50) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `createTime` timestamp(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) ON UPDATE CURRENT_TIMESTAMP(0),
  PRIMARY KEY (`session`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = utf8 COLLATE = utf8_unicode_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;

/*Social Network TABLES*/

/** 
 * Social Network bdcreaet.sql File
 *
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Ravith Botejue
 * @author     G.W.R. Sandaruwan <sandaruwan@opensource.lk> <rekasandaruwan@gmail.com
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    shana
 * @subpackage sn
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

INSERT INTO `sn_roles` (`role_id` , `role_category`, `role_name` ,`description`)
VALUES ('sn1', 'sn', 'sn admin','Social Network Administrator'),
       ('sn2', 'sn', 'sn moderator', 'Moderate the Social Network'),
       ('sn3', 'sn', 'sn user', 'User of Social Network'),
       ('f1', 'forum', 'sn forum admin', 'Forum Administrator'),
       ('f2', 'forum', 'forum admin', 'Administrator the Selected Forum'),
       ('f3', 'forum', 'moderator', 'Moderate the Selected Forum'),
       ('f4', 'forum', 'user', 'Normal User'),
       ('f5', 'forum', 'guest', 'Guest'),
       ('g1', 'group', 'sn group admin', 'Group Administrator'),
       ('g2', 'group', 'group admin', 'Administrator for the Selected Group'),
       ('g3', 'group', 'moderator', 'Moderate the Selected Group'),
       ('g4', 'group', 'user', 'Group Member'),
       ('g5', 'group', 'guest', 'Guest');

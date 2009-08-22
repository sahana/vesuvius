<?php

/**
* Picture class
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author       Antonio Alcorn
* @author       Giovanni Capalbo
* @author		Sylvia Hristakeva
* @author		Kumud Nepal
* @author		Ernel Wint
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @copyright    Trinity Humanitarian-FOSS Project - http://www.cs.trincoll.edu/hfoss
* @package      sahana
* @subpackage   vm
* @tutorial
* @license        http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/

/**
 * VMPicture
 * represents a picture stored in the VM module.
 */
class VMPicture extends Model {
	public	$img_uuid,								// unique ID for this image
			$p_uuid,								// ID of the associated volunteer (can be null)
			$original,								// [binary] the original image first uploaded
			$image_data,								// [binary] image data for the full-size image
			$thumb_data,								// [binary] image data for the thumbnail
			$name,									// original filename from upload
			$type,									// MIME type (e.g. "image/jpeg")
			$size,									// length of original data in bytes
			$width = 		VM_IMAGE_BIG_WIDTH,		// max width for image
			$height = 		VM_IMAGE_BIG_HEIGHT,	// max height for image
			$thumb_width	 =	VM_IMAGE_THUMB_WIDTH,	// max width for thumbnail
			$thumb_height =	VM_IMAGE_THUMB_HEIGHT;	// max height for thumbnail

	/**
	 * VMPicture (constructor)
	 * @param int $img_uuid
	 * If passed an image ID, it will populate itself with the pre-existing data for that image.
	 */
	function VMPicture($img_uuid=null) {
		if($img_uuid) {
			Model::Model();
			$this->img_uuid = $img_uuid;
			list(
				$this->image_data,
				$this->thumb_data,
				$this->p_uuid,
				$this->width,
				$this->height,
				$this->thumb_width,
				$this->thumb_height,
				$this->type,
				$this->name
			) = $this->dao->getVMPicture($img_uuid);
		}
	}

	/**
	 * resize()
	 * Generate resized image and thumbnail. This is called when the image is first uploaded,
	 * and saved in the database. When the image or thumbnail is subsequently displayed, it
	 * is fetched from the database.
	 */
	function resize() {
		// attempt to parse the original (uploaded) image data
		if(!($original = @imagecreatefromstring($this->original)))
			return false;
		$original_width = imagesx($original);
		$original_height = imagesy($original);

		// get the aspect ratio of the original image
		$aspect = $original_width / $original_height;

		// set width and height of image and thumbnail, constraining to the specified max width and height for each
		$width	= $aspect <= 1? $this->height*$aspect:$this->width;
		$height = $aspect <= 1? $this->height:$this->width/$aspect;

		$thumb_width	 =	$aspect <= 1? $this->thumb_height*$aspect:$this->thumb_width;
		$thumb_height =	$aspect <= 1? $this->thumb_height:$this->thumb_width/$aspect;

		// create a blank image resource of the right size for the image and thumb
		$image = imagecreatetruecolor($width, $height);
		$thumb = imagecreatetruecolor($thumb_width, $thumb_height);

		// do the resizing
		imagecopyresized($image, $original, 0, 0, 0, 0, $width, $height, $original_width, $original_height);
		imagecopyresized($thumb, $original, 0, 0, 0, 0, $thumb_width, $thumb_height, $original_width, $original_height);

		// sample the images and save the data to our instance variables
		// imagejpeg() et al. don't support returing the data, so we have to use output buffering
		ob_start();
		imagejpeg($image, null, VM_IMAGE_QUALITY);
		$this->image_data = ob_get_clean();

		ob_start();
		imagejpeg($thumb, null, VM_IMAGE_QUALITY);
		$this->thumb_data = ob_get_clean();

		// set the MIME type
		// for now we're always using JPEG
		$this->type = 'image/jpeg';

		return true;
	}
	/**
	 * save()
	 * Save the data in the VMPicture object, including image data, to the database.
	 */
	function save() {
		global $global;
		// generate a new UUID, if we need it
		if(empty($this->img_uuid)) {
			require_once($global['approot'].'inc/lib_uuid.inc');
			$this->img_uuid = shn_create_uuid();
		}
		Model::Model();
		$this->dao->saveVMPicture($this);
	}
	/**
	 * display()
	 * outputs the image, with headers
	 * for now it's always JPEG
	 */
	function display() {
		if(empty($this->image_data))
			return false;
		else {
			header("Content-Type: {$this->type}");
			echo($this->image_data);
		}
	}

	/**
	 * displayThumb()
	 * outputs the thumbnail, with headers
	 */
	function displayThumb() {
		if(empty($this->thumb_data))
			return false;
		else {
			header("Content-Type: {$this->type}");
			echo($this->thumb_data);
		}
	}
}

/**
 * shn_image_vm_display_image()
 * This lets us use Sahana's 'stream' functionality to display an image without resorting to
 * an extra file in /tmp.
 * Sahana automatically calls this, according to the shn_[stream]_[mod]_[act]() naming convention.
 */
function shn_image_vm_display_image() {
	// we're not going through our controller here, so we need to set up the database.
	shn_vm_load_db();
	$img_uuid = $_GET['id'];
	$size = $_GET['size'];
	$p = new VMPicture($img_uuid);
	if($size == 'thumb')
		$p->displayThumb();
	else
		$p->display();

}



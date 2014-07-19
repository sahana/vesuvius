<?php
/*
* @class              googlUrl
* @author             Akshay Kalose (http://www.kalose.net/)
* @release            12/18/2013
* @version            1.0
*
* Usage:
* Instantiate:        $googl = new googlUrl('http://google.com/');
* Recieve Short Link: $short = $googl->short();
* 
* Instantiate:        $googl = new googlUrl('http://goo.gl/DE1y3W');
* Recieve Long Link:  $long = $googl->long();
*/
class googlUrl
{
	//Key is recommended, but not required.
	private $key = '';
	public $short, $long;

	public function __construct($url)
	{
		if (strpos($url, 'goo.gl') === false) {
			$this->long = $url;
			$this->short = null;
		} else {
			$this->long = null;
			$this->short = $url;
		}
	}

	public function short()
	{
		if (isset($this->short)) {
			return $this->short;
		}

		if (isset($this->long)) {
			if (function_exists('curl_init')) {
				$curl = curl_init();
				$sendData = '{"longUrl":"' . $this->long . '"}';
				curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, !(strpos($config['https'], 'https') === false));
				curl_setopt($curl, CURLOPT_URL, 'https://www.googleapis.com/urlshortener/v1/url?' . ($this->key ? $this->key . '&' : ''));
				curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
				curl_setopt($curl, CURLOPT_POST, true);
				curl_setopt($curl, CURLOPT_POSTFIELDS, $sendData);
				curl_setopt($curl, CURLOPT_HTTPHEADER, Array('Content-Type: application/json'));
				$result = json_decode(curl_exec($curl));
				curl_close($curl);
				return $result->id;
			} else {
				add_error(_t('Warning: The cURL extension is not found. Please check your PHP configuration.'));
			}
		} else {
			return false;
		}
	}

	public function long()
	{
		if (isset($this->long)) {
			return $this->long;
		}

		if (isset($this->short)) {
			if (function_exists('curl_init')) {
				$curl = curl_init();
				curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, !(strpos($config['https'], 'https') === false));
				curl_setopt($curl, CURLOPT_URL, 'https://www.googleapis.com/urlshortener/v1/url?' . ($this->key ? $this->key . '&' : '') . 'shortUrl=' . $this->short);
				curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
				curl_setopt($curl, CURLOPT_HTTPGET, true);
				$result = json_decode(curl_exec($curl));
				curl_close($curl);
				return $result->longUrl;
			} else {
				add_error(_t('Warning: The cURL extension is not found. Please check your PHP configuration.'));
			}
		} else {
			return false;
		}
	}
}

<?php
class HttpFetch
{
    var $url;
    var $port;
    var $type;
    var $proxy_host;
    var $proxy_port;
    var $proxy_user;
    var $proxy_pass;

    var $agent;
    var $referer;
    
    var $save_to_tmp;
    var $save_to_location;

    var $timeout;

    function HttpFetch(){
        $this->port = 80;
        $this->type = 'GET';
        $this->proxy_host = '';
        $this->proxy_port = '';
        $this->proxy_user = '';
        $this->proxy_pass = '';
        
        $this->agent = 'Sahana HttpFetch 0.1';
        $this->referer = '';
    
        $this->save_to_tmp = false;
        $this->save_to_location = false;

        $this->timeout = 30;
    }

    function fetch($url='')
    {
        
        if($url)
            $this->url = $url;

        if($this->save_to_tmp)
            $out_file = mktime();
        
        if($this->save_to_location)
           $out_file = $this->save_to_location; 


        $url_arr = parse_url($url);
        $path = $url_arr['path'].
                    ($url_arr['query']?"?{$url_arr['query']}":'').
                    ($url_arr['fragment']?"#{$url_arr['fragment']}":"");

        //if(function_exists('curl_init')){
            //use curl library
        //}else{
            $fp = fsockopen($url_arr['host'], $this->port , $errno, $errstr, $this->timeout);
            if (!$fp) {
                add_error("$errstr ($errno)<br />");
                return false;
            }else{

                if($out_file)
                    $out_fp = fopen($out_file, 'w');
                
                $out = "{$this->type} $path HTTP/1.1\r\n";
                $out .= "Host: {$url_arr['host']}\r\n";
                $out .= "User-Agent: {$this->agent}\r\n";
                $out .= "Connection: Close\r\n\r\n";

                fwrite($fp, $out);
                while (!feof($fp)) {
                    $ch = fgets($fp, 128);
                    #debug($ch);
                    //ignore the head
                    if($content){
                        if($out_fp)
                            fwrite($out_fp, $ch);
                        else
                            $return .= $ch;
                    }else{
                        //catch errors
                        //200 OK
                        if(preg_match("/HTTP\/1\.1 (.*?) (.*)/",$ch,$matches) ){
                            if(trim($matches[1]) != 200){
                                add_error("{$matches[1]} {$matches[2]}");
                                return false;
                            }
                        }

                        if(preg_match("/Content-Type:/",$ch) ){
                            $content = true;
                        }
                    }
                }
                fclose($fp);

                if($out_fp)
                    fclose($out_fp);

                return $return;
            }
        //}
    }
}


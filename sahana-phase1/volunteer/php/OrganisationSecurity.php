<?php

if ((!$_COOKIE['username']) || 
    (!$_COOKIE['password']) ||
    (!$_COOKIE['person_id'])) {
  clear_cookies();
  header ("Location: $login_page");
}

?>
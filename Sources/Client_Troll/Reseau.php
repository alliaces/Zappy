<?php


class Reseau
{
	var $address;
	var $port;
	var $last_request;
	var $socket;
	var $receive; 
	static $nb_broadcast;

	function __construct(&$_address, $_port) 
	{
		$this->address = $_address;
		$this->port = $_port;
		echo "Connexion TCP/IP\n";
		$this->socket = @socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
		if ($this->socket === false) 
			{
	    		echo "socket_create() a échoué : " . socket_strerror(socket_last_error()) . "\n";
	    		exit;
			}
		else
	    	echo "OK.\n";

		if (@socket_connect($this->socket, $this->address, $this->port) === false)
			{
	    		echo "socket_connect() a échoué : " . socket_strerror(socket_last_error()) . "\n";
				exit;    		
			}
		else
	    	echo "Connection réussi\n";
	    $this->nb_broadcast = 0;
	}

	public function receive(Receive &$r)
	{
		$this->receive = $r;
	}

	public function first_read()
	{
		$this->last_request = "";
		while (($out = @socket_read($this->socket, 2048, PHP_BINARY_READ)))
		{
			if ($out === false)
			{
				echo "socket_read a échoué : " . socket_strerror(socket_last_error()) . "\n";
				exit;
			}
			$this->last_request .= $out;
			if (strlen($out) < 2048)
				break;
		}
		echo $this->last_request;
		if (($this->last_request = substr($this->last_request, 0, -1)) == "mort")
		{
			echo "nb_broadcast = " . $this->nb_broadcast . "\n";
			exit;
		}
		return $this->last_request;
	}

	public function read()
	{
		$this->last_request = "";
		while (($out = @socket_read($this->socket, 102400, PHP_NORMAL_READ)))
		{
			if ($out === false)
			{
				echo "socket_read a échoué : " . socket_strerror(socket_last_error()) . "\n";
				exit;
			}
			$this->last_request .= $out;
			if (strlen($out) < 102400)
				break;
		}
		echo "read : $this->last_request";
		if (($this->last_request = substr($this->last_request, 0, -1)) == "mort")
			exit;
		if (substr($this->last_request, 0, 8) == "message ")
		{
			$this->receive->broadcast($this->last_request);
			return ($this->last_request = $this->read());
		}
		else if (substr($this->last_request, 0, 13) == "deplacement: ")
		{
			$this->receive->expulse($this->last_request);
			return ($this->last_request = $this->read());
		}
		else if (substr($this->last_request, 0, 16) == "niveau actuel : ")
		{
			$this->receive->incantation($this->last_request);
			return ($this->last_request = $this->read());
		}
		else if (is_numeric($this->last_request))
		{
			$this->receive->connect_nbr($this->last_request);
			return ($this->last_request = $this->read());
		}
		return $this->last_request;
	}

	public function write($in)
	{
		$in .= "\n";
		$ret = 0;
		echo "write : $in";
		$str_in = strlen($in);
		while (($ret = @socket_write($this->socket, $in, strlen($in))) != $str_in)
		{
			if ($ret === false)
			{
				echo "socket_write a échoué : " . socket_strerror(socket_last_error()) . "\n";
				exit;
			}
			$str_in -= $ret;
			$in = substr($in, $ret);
		}
	}

	public function request($in)
	{
		$this->write($in);
		return ($this->read());
	}

	function __destruct()
	{
		echo "Fermeture du socket...\n";
		socket_close($this->socket);
		echo "OK.\n";
	}
}

?>

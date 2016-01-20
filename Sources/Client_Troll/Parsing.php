<?php

class Parsing
{
	public $team = "";
	public $port = 0;
	public $addr = "127.0.0.1";

	function __construct($argc, &$argv) 
	{	
		if ($argc != 5 && $argc != 7)
			exit("Usage : " . $argv[0] . " -n nom_d_équipe -p port [-h nom_de_la_machine]\n");

		$i = 1;
		$b_addr = false;
		while ($i < $argc)
		{
			if ($argv[$i] == "-n")
			{
				if ($this->team == "")
					$this->team = $argv[++$i];
				else
					exit("Usage : " . $argv[0] . " -n nom_d_équipe -p port [-h nom_de_la_machine]\n");
			}
			else if ($argv[$i] == "-p")
			{
				if ($this->port == "")
				{
					if(is_numeric($argv[++$i]))
						$this->port = $argv[$i];
					else
						exit("Le port est obligatoirement un nombre !\n");
				}
				else
					exit("Usage : " . $argv[0] . " -n nom_d_équipe -p port [-h nom_de_la_machine]\n");
			}
			else if ($argv[$i] == "-h")
			{
				if ($b_addr === false)
				{
					$b_addr = true;
					$this->addr = $argv[++$i];
				}
				else
					exit("Usage : " . $argv[0] . " -n nom_d_équipe -p port [-h nom_de_la_machine]\n");
			}
			else
				exit("Usage : " . $argv[0] . " -n nom_d_équipe -p port [-h nom_de_la_machine]\n");
			$i++;
		}
		if ($this->port == 0 || $this->team == "")
			exit("Usage : " . $argv[0] . " -n nom_d_équipe -p port [-h nom_de_la_machine]\n");
	}
}

?>
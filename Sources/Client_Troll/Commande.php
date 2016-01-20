<?php

class Commande
{

	var $res;
	var $out;
	var $nb_command;

	function __construct(Reseau &$r)
	{
		$this->res = $r;
		$this->nb_command = 0;
	}
	
	function avance()
	{
		$this->nb_command++;
		return ($this->out = $this->res->request("avance"));
	}

	function droite()
	{
		$this->nb_command++;
		return ($this->out = $this->res->request("droite"));
	}

	function gauche()
	{
		$this->nb_command++;
		return ($this->out = $this->res->request("gauche"));
	}

	function count_virgule(&$in)
	{
		if (substr_count($in, ",") > 4)
		{
			$len = 0;
			for ($i = 0; $i < 4; $i++)
				$len = strpos($in, ",", $len) + 1;
			$in = substr($in, 0, $len - 1);
		}
		return ($in);
	}

	function splitCommand($answer)
	{
		$tmp = $answer;
		$answer = substr($answer, 1, -1);
		$this->count_virgule($answer);
		$cases = split(",", $answer);
		foreach ($cases as $key => $string) 
		{
			if (strlen($string) > 0)
				if ($string[0] == ' ')
					$cases[$key] = substr($string, 1);
			$cases[$key] = explode(" ", $cases[$key]);
		}
		$this->out = $cases;
		if (count($cases) < 2)
		{
			exit();
		}
		return $cases;
	}

function voirBis()
	{
		$this->nb_command++;
		$this->out = $this->res->request("voir");
		return ($this->splitCommand($this->out));
	}

	function voir()
	{
		$this->nb_command++;
		$this->out = $this->res->request("voir");
		$this->out = substr($this->out, 1, -1);
		$this->out = $this->count_virgule($this->out);
		$cases = explode(",", $this->out);
		foreach ($cases as $key => $string) 
		{
			if (strlen($string) > 0)
				if ($string[0] == ' ')
					$cases[$key] = substr($string, 1);

			$cases[$key] = explode(" ", $cases[$key]);
		}
		$this->out = $cases;
		if (count($cases) < 2)
		{
			exit();
		}
		return $cases;
	}

	function inventaire()
	{
		$this->nb_command++;
		if (($this->out = $this->res->request("inventaire")) == "ko")
			$this->out = $this->res->read();
		$this->out = substr($this->out, 1, -1);
		$cases = explode(",", $this->out);
		foreach ($cases as $key => $string) 
		{
			if (strlen($string) > 0)
				if ($string[0] == ' ')
					$cases[$key] = substr($string, 1);
			$cases[$key] = explode(" ", $cases[$key]);
		}
		$this->out = $cases;
		return $cases;
	}

	function prend($objet)
	{
		$this->nb_command++;
		$this->out = $this->res->request("prend " . $objet);
		return ($this->out);
	}

	function pose(&$objet)
	{
		$this->nb_command++;
		return ($this->out = $this->res->request("pose " . $objet));
	}

	function expulse()
	{
		$this->nb_command++;
		return ($this->out = $this->res->request("expulse"));
	}

	function broadcast($texte)
	{
		$this->nb_command++;
		return ($this->out = $this->res->request("broadcast " . $texte));
	}

	function reset()
	{
		$this->nb_command = 0;
	}

	function incantation()
	{
		$this->out = $this->res->request("incantation");
		return ($this->out);
	}

	function fork()
	{
		return ($this->out = $this->res->request("fork"));
	}

}

Class Receive
{
	var $broadcast;
	var $lvl;
	var $b_direction;
	var $b_id;
	var $play;
	var $incantation;
	var $ready;
	var $connect_nbr;

	function __construct(Joueur &$p)
	{
		$this->broadcast = false;
		$this->b_id = -1;
		$this->play = $p;
		$this->incantation = false;
		$this->ready = false;
		$this->connect_nbr = 0;
	}

	function broadcast(&$in)
	{
		$in[9] = " ";
		$arg = explode(" ", $in);
		$len = count($arg);
		if ($len > 2 && $arg[2] == "1") // Appel à l'élévation
		{
			if ($this->b_id == -1 && $this->play->lvl == (int)$arg[4] && (bool)$arg[5] == "1")
				{
					$this->b_id = (int)$arg[3];
					$this->b_direction = (int)$arg[1];
					$this->broadcast = true;
					$this->ready = true;
				}
			else if ($this->b_id == (int)$arg[3])
			{
				$this->ready = true;
				$this->b_direction = (int)$arg[1];
				if ((bool)$arg[5] == "0")
				{
					$this->b_id = -1;
					$this->b_direction = (int)$arg[1];
					$this->broadcast = false;
				}
			}
		}
	}

	function connect_nbr(&$in)
	{
		$this->connect_nbr = (int)$in;
	}

	function expulse(&$in) {}

	function incantation(&$in)
	{
		$this->play->lvl = (int)substr($in, 16);
		$this->incantation = false;
	}
}
?>
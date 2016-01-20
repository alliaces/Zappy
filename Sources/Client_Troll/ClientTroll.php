#!/usr/bin/php
<?php

include "Parsing.php";
include "Reseau.php";
include "Commande.php";
include "Joueur.php";

$parse = new Parsing($argc, $argv);
$res = new Reseau($parse->addr, $parse->port);
$play = new Joueur($res);
$res->first_read(); // BIENVENUE
$res->write($parse->team);
$nb_joueur = $res->first_read(); // NB JOUEURS
if ($nb_joueur == "ko" || $nb_joueur == "0")
	exit;
$res->first_read(); // TAILLE MAP

boucle();

function survivor()
{
	global $play;
	global $levelFood;

	print("\033[32m");
	$nourriture = 0;
	$play->command->reset();
	while ($nourriture < 30)
	{
		if (($tmp = (int)($play->command->nb_command / 18)) > 0)
		{
			$nourriture -= $tmp;
			$play->command->nb_command -= $tmp * 18; 
		}
		if (($eaten = $play->takeFirstElementInView("nourriture", 10)) > 0)
			$nourriture += $eaten;
		else
			$play->avanceRandom();
	}
	print("\033[0;0m");
}

function trollMode()
{
	global $play;

	for ($i = 0; $i < 3; $i++)
	{
		if ($play->findPlayersToExpulse() == False)
		{
			$play->avanceRandom();
			$play->toutPrendre();
		}

	}
}

function boucle()
{
	global $play;

	while (42) // Boucle de l'IA
	{
		$out = $play->command->inventaire();
		if (count($out) > 1)
		{
			if (((int)$out[0][1]) >= 20)
			{
				if ($play->lvl > 1)
					trollMode();
				else
				{
					if ($play->checkRessources($out) == True)
					{
						$play->toutPrendre();
						$play->poseNecessaireIncantation();
						$play->command->incantation();
					}
					else
					{
						$play->toutPrendre();
						$play->avanceRandom();
					}
				}
			}
			else
				survivor();
		}
	}
}
?>
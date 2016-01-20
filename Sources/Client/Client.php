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
$levelFood = [20, 30, 30, 30, 40, 40, 60, 60, 80];

boucle();

function survivor()
{
	global $play;
	global $levelFood;

	print("\033[32m");
	$nourriture = 0;
	$play->command->reset();
	while ($nourriture < $levelFood[$play->lvl])
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

function entreNiveau()
{
	global $play;

	if ($play->lvl == 8)
	{
		$play->toutPoser();
		$nourriture = $play->command->inventaire();
		$i = 0;
		while ((int)$nourriture[0][1] > 20)
			{
				$play->avanceRandomWithCheck();
				if ($i == 10)
				{
					$nourriture = $play->command->inventaire();
					$i = 0;
				}
				$i++;
			}
	}
	else
	{
		$nourriture = $play->command->inventaire();
		if ((int)$nourriture[0][1] > 20)
			$play->PoseNonNecessaire();		
	}
}

function boucle()
{
	global $res;
	global $play;
	global $levelFood;

	while (42) // Boucle de l'IA
	{
		$out = $play->command->inventaire();
		if (count($out) > 1)
		{
			if (((int)$out[0][1]) >= 20 && $play->lvl < 8)
			{
				if ($play->checkSlotTeam() == True)
					continue ;
				if ($play->receive->broadcast)
					$play->goToElevation();
				else 
				{
					if ($play->checkRessources($out))
						$play->elevation();
					else
					{
						print("\033[33m");
						$play->PrendreSeulNecessaire();
						$play->PoseNonNecessaire();
						$play->avanceRandomWithCheck();
						print("\033[0;0m");
					}
				}
			}
			else
			{	
				survivor();			
				entreNiveau($nourriture);
			}
		}
	}
}
?>
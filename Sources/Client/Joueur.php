<?php
	
#include "Parsing.php";
#include "Reseau.php";
#include "Commande.php";

    function printError($str)
    {
        print("\033[31m".$str."\033[0;0m\n");
    }

	class Joueur
	{
		// Eléments de notre inventaire
    	public $lvl;
    	public $id;
    	private $team;

    	public function __construct(Reseau &$r)
    	{
            $this->incantNeeds = 
            [
                [1, 1, 0, 0, 0, 0, 0], #hors niveau
                [1, 1, 0, 0, 0, 0, 0], #Niveau 1 - 2
                [2, 1, 1, 1, 0, 0, 0], #Niveau 2 - 3
                [2, 2, 0, 1, 0, 2, 0], #Niveau 3 - 4
                [4, 1, 1, 2, 0, 1, 0], #Niveau 4 - 5
                [4, 1, 2, 1, 3, 0, 0], #Niveau 5 - 6
                [6, 1, 2, 3, 0, 1, 0], #Niveau 6 - 7
                [6, 2, 2, 2, 2, 2, 1], #Niveau 7 - 8
                [0, 0, 0, 0, 0, 0, 0]  #Niveau qui n'existe pas
            ];
            $this->correspondingStone = 
            [
                [0, "joueur"],
                [1, "linemate"],
                [2, "deraumere"],
                [3, "sibur"],
                [4, "mendiane"],
                [5, "phiras"],
                [6, "thystame"]
            ];
            $this->incantNeedsForNow = 
            [
                [0, 1, 0, 0, 0, 0, 0],
                ["joueur", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"]
            ];
            $this->lvl = 1;
    		$this->id = rand(0, 1000000000);
    		$this->personOnMyCase = 1;
            $this->reseau = $r;
            $this->command = new Commande($this->reseau);
            $this->receive = new Receive($this);
            $this->reseau->receive($this->receive);
            $this->nbSlotTeam = 2;
    	}

    	public function __destruct()
    	{

    	}

        public function checkSlotTeam()
        {
            if ($this->nbSlotTeam > 0)
            {
                $this->nbSlotTeam--;
                $this->command->fork();
                $this->avanceRandom();
                return (True);
            }
            return (False);
        }

        public function computeNeedsForIncant(&$inventaire)
        {
            $this->incantNeedsForNow[0][0] = $this->incantNeeds[$this->lvl][0] - $this->personOnMyCase;
            for ($i = 1; $i < 7; $i++)
                {
                    $tmp = $this->incantNeeds[$this->lvl][$i] - (int) $inventaire[$i][1];
                    if ($tmp < 0)
                        $tmp = 0;
                    $this->incantNeedsForNow[0][$i] = $tmp;
                }
            return ($this->incantNeedsForNow);
        }

        public function checkRessources(&$inventaire)
        {
            $this->computeNeedsForIncant($inventaire);
            $i = 1;
            while ($i < 7)
            {
                if ($this->incantNeedsForNow[0][$i] != 0)
                    return false;
                $i++;
            }
            return true;
        }

        public function avanceRandom()
        {
            $result = rand(0, 8);
            if ($result < 6)
                $this->command->avance();
            else
            {
                if ($result == 6)
                {
                    $this->command->droite();
                    $this->command->avance();
                }
                else
                {
                    $this->command->gauche();
                    $this->command->avance();
                }
            }
        }

        function CheckPlayerToAvance()
        {
            $vu = $this->command->voir();
            foreach ($vu[2] as $key => $value)
            {
                if ($value == "joueur")
                    return (false);
            }
            return (true);
        }

        function avanceRandomWithCheck()
        {
           $result = rand(0, 8);
            if ($result < 6)
                if ($this->CheckPlayerToAvance())
                    $this->command->avance();
            else
            {
                if ($result == 6)
                {
                    $this->command->droite();
                    if ($this->CheckPlayerToAvance())
                        $this->command->avance();
                }
                else
                {
                    $this->command->gauche();
                    if ($this->CheckPlayerToAvance())
                        $this->command->avance();
                }
            }            
        }

        private function voirEtPlus()
        {
            $vu = $this->command->voir();
            $this->personOnMyCase = $this->countCaseElement($vu[0], "joueur");
            if (($nb = $this->countCaseElement($vu[0], "nourriture")) > 0)
            {
                for ($i = 0; $i < $nb; $i++)
                {
                    $this->command->prend("nourriture");
                }
            }
            if ($nb > 0)
                return ($this->command->voir());
            return ($vu);
        }

        private function countCaseElement($case, $element)
        {
            $counted = 0;
            $i = 0;
            $size = count($case);
            while ($i < $size)
            {
                if ($case[$i] == $element)
                    $counted++;
                $i++;
            }
            return ($counted);
        }

        private function searchFirstElement(&$array, $element)
        {
            $i = 1;
            $nb = count($array);
            $retVal = [0, 0];

            if ($nb > 2)
            {
                if (($nbElem = $this->countCaseElement($array[2], $element)) > 0 && $this->countCaseElement($array[2], "joueur") < 3)
                {
                    $retVal[0] = 2;
                    $retVal[1] = $nbElem;
                }
            }
            while ($i < $nb)
            {
                if (($nbElem = $this->countCaseElement($array[$i], $element)) > 0 && $this->countCaseElement($array[$i], "joueur") < 3)
                {
                    $retVal[0] = $i;
                    $retVal[1] = $nbElem;
                    return ($retVal);
                }
                $i++;
            }
            return ($retVal);
        }

        private function searchMoreElement(&$array, $element)
        {
            $i = 0;
            $nb = count($array);
            $retVal = [0, 0];
            while ($i < $nb)
            {
                if (($nbElem = $this->countCaseElement($array[i], $element)) > $retVal[1])
                {
                    $retVal[0] = $i;
                    $retVal[1] = $nbElem;
                }
                $i++;
            }
            return ($retVal);
        }

        private function findRangeView($caseNumber, &$lineView, &$middle)
        {
            if ($caseNumber == 0)
                return (0);
            $range = 1;
            $nb = 3;
            $lower = 1;   
            $upper = 3;
            
            while ($caseNumber > $upper)
            {
                $nb += 2;
                $lower = $upper + 1;
                $upper = ($lower + $nb) - 1;
                $range++;
            }
            for ($i = 0; $i < $nb; $i++)
            {
                array_push($lineView, $lower++);
            }
            $middle = (int)($nb / 2);
            return ($range);
        }

        private function goToCaseInView($caseNumber) #acceder a la case demandée situé dans la vue
        {
            $diagonal = 2;
            $nbDiag = 0; #nombre de diagonales a faire avant d'etre en face de la case
            $arrayLine = [];
            $middle = 0;
            $range = $this->findRangeView($caseNumber, $arrayLine, $middle);
            $j = 0;
            $i = 0;
            if ($caseNumber == 0)
                return;
            if ($caseNumber > $arrayLine[$middle])
            {
                $diagonal = 8;
                $nbDiag = $caseNumber - $arrayLine[$middle];
            }
            else
            {
                $nbDiag = $arrayLine[$middle] - $caseNumber;
            }

            while ($j < $nbDiag) #nombre de diagonale a faire pour etre en face de la case a atteindre
            {
                $this->forwardOneCase($diagonal);
                $i++;
                $j++;
            }
            while ($i < $range) #nombre d'avancees a faire pour atteindre la case
            {
                $this->forwardOneCase(1);
                $i++;
            }
        }

        public function takeFirstElementInView($element, $max)
        {
            $vu = $this->voirEtPlus();
            $elementArray = $this->searchFirstElement($vu, $element);
            if ($elementArray[1] < 1)
            {
                return (False);
            }
            $nb = $elementArray[1];
            $this->goToCaseInView($elementArray[0]);
            for ($i = 0; $i < $nb and $i < $max; $i++)
            {
                $this->command->prend($element);
            }
            return ($nb);
        }

        public function takeMoreElementInView($element, $max)
        {
            $vu = $this->command->voirEtPlus();            
            $elementArray = $this->searchMoreElement($vu, $element);
            if ($elementArray[1] < 1)
                return (False);
            $nb = $elementArray[1];
            $this->goToCaseInView($elementArray[0]);
            for ($i = 0; $i < $nb and $i < $max; $i++)
            {
                $this->command->prend($element);
            }
            return ($nb);
        }

        private function forwardOneCase($direction)
        {
            if ($direction == 0)
                return;
            $this->command->avance();
            if ($direction == 2)
                {
                    $this->command->gauche();
                    $this->command->avance();
                    $this->command->droite();
                }
            else
                if ($direction == 8)
                {
                    $this->command->droite();
                    $this->command->avance();
                    $this->command->gauche();
                }
        }

		public function forwardDirection(&$direction)
		{
            if ($direction < 3 or $direction > 7)
            {
                $this->forwardOneCase($direction);
                return ;
            }
            else
            {
                while (!($direction < 3 or $direction > 7))
                {
                    if ($direction < 6)
                    {
                        $direction -= 2;
                        $this->command->gauche();
                    }
                    else
                    {
                        $direction += 2;
                        if ($direction == 9)
                            $direction = 1;
                        $this->command->droite();
                    }
                }
                $this->forwardOneCase($direction);
            }
		}

        function wait_broadcast()
        {
            $this->nourriture = $this->command->inventaire();
            $init_nourriture = (int)$this->nourriture[0][1];
            while ((int)$this->nourriture[0][1] >= 20 && $this->receive->ready == false)
            {
                $this->nourriture = $this->command->inventaire();
                if (($init_nourriture - (int)$this->nourriture[0][1]) > 2)
                {
                    $this->receive->ready = false;
                    $this->receive->broadcast = false;
                    $this->receive->b_id = -1;
                    return ("ko");
                }
            }
            $this->receive->ready = false;
        }

        function goToElevation()
        {
            $this->command->reset();
            $this->nourriture = $this->command->inventaire();
            $direction = $this->receive->b_direction;
            while ($this->receive->broadcast == true && (int)$this->nourriture[0][1] >= 20)
            {
                if ($this->wait_broadcast() == "ko")
                    return;
                if ($this->receive->b_direction == 0)
                {
                    if ($this->wait_broadcast() == "ko")
                        return;
                    $this->forwardDirection($this->receive->b_direction);
                    $this->receive->incantation = true;
                    $vu = $this->command->voir();
                    $this->personOnMyCase = $this->countCaseElement($vu[0], "joueur");
                    $personToHave = $this->incantNeeds[$this->lvl][0];
                    $quit = false;
                    $this->nourriture = $this->command->inventaire();
                    $init_nourriture = (int)$this->nourriture[0][1];
                    while ($this->receive->incantation == true && (int)$this->nourriture[0][1] >= 20 && ($init_nourriture - (int)$this->nourriture[0][1]) < 15 && $this->personOnMyCase != 1 && $quit == false)
                    {
                        $vu = $this->voirEtPlus();
                        $this->nourriture = $this->command->inventaire();
                        while ($this->receive->incantation == true && $this->personOnMyCase == $personToHave && (int)$this->nourriture[0][1] >= 20)
                        {
                            $vu = $this->voirEtPlus();
                            $this->nourriture = $this->command->inventaire();
                            $quit = true;                        
                        }
                    }
                    $this->receive->incantation = false;
                }
                $this->forwardDirection($this->receive->b_direction);
            }
        }

        function toutPrendre()
        {
            $joueur = 0;
            $vu = $this->voirEtPlus();
            foreach ($vu[0] as $key => $value)
            {
                if ($value == "joueur")
                    $joueur++;
                else
                    $this->command->prend($value);
            }
            $this->personOnMyCase = $joueur;
        }

        private function takeAndCheckElement($element)
        {
            for ($i = 1; $i < 7; $i++)
            {
                if ($element == $this->incantNeedsForNow[1][$i])                
                {
                    if ($this->incantNeedsForNow[0][$i] > 0)
                        {
                            $this->command->prend($element);
                            $this->incantNeedsForNow[0][$i]--;
                        }
                }
            }
        }

        public function prendreSeulNecessaire()
        {
            $vu = $this->voirEtPlus();
            if ($this->countCaseElement($vu[0], "joueur") > 1)
                return;
            $nb = count($vu[0]);
            for ($i = 0; $i < $nb; $i++)
            {
                if ($vu[0][$i] != "joueur" && $vu[0][$i] != "nourriture")
                {
                    $this->takeAndCheckElement($vu[0][$i]);
                }
            }
        }

        function poseNonNecessaire()
        {
            $pierre = $this->command->inventaire();
            foreach ($pierre as $key => $value)
            {
                while ($value[1] > 0 && $key > 0 && ($value[1] - $this->incantNeeds[$this->lvl][$key] > 0))
                {
                    $this->command->pose($value[0]);
                    $value[1]--;
                }
            }
        }

        function toutPoser()
        {
            $pierre = $this->command->inventaire();
            foreach ($pierre as $key => $value) 
            {
                while ($value[1] > 0 && $key > 0)
                {
                    $this->command->pose($value[0]);
                    $value[1]--;
                }
            }
        }

        function poseNecessaireIncantation()
        {
            for ($i = 1; $i < 7; $i++)
            {
                $needs = $this->incantNeeds[$this->lvl][$i];
                while ($needs > 0)
                {
                    if ($this->command->pose($this->correspondingStone[$i][1]) == "ko")
                        return ("ko");
                    $needs--;
                }
            }
            return ("ok");
        }

        function elevation()
        {
            $reset = 0;
            $init = true;
            $nourriture = $this->command->inventaire();
            while ((int)$nourriture[0][1] >= 20)
            {
                if ($reset == 5)
                {
                    $reset = 0;
                    $nourriture = $this->command->inventaire();
                }
                $this->toutPrendre();
                if ($init == true && $this->receive->broadcast == true)
                    return;
                $init = false;
                if ($this->incantNeeds[$this->lvl][0] - $this->personOnMyCase > 0)
                    $this->command->broadcast("1 $this->id $this->lvl 1");
                else if ($this->incantNeeds[$this->lvl][0] - $this->personOnMyCase == 0)
                {
                    if ($this->lvl != 1)
                        $this->command->broadcast("1 $this->id $this->lvl 0");
                    $out = $this->command->inventaire();
                    if ((int)$out[0][1] < 10)
                        break;
                    if ($this->poseNecessaireIncantation() == "ko")
                        break;
                    if ($this->incantNeeds[$this->lvl][0] - $this->personOnMyCase == 0)
                        return ($this->command->incantation());
               }
               $reset++;
            }
            $this->command->broadcast("1 $this->id $this->lvl 0");
        }
	}
?>
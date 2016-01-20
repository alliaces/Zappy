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

        private function searchCasePlayersToExpulse(&$array)
        {
            $i = 0;
            $nb = count($array);
            $retVal = [0, 0];
            while ($i < $nb)
            {
                if (($nbElem = $this->countCaseElement($array[$i], "nourriture")) > 1)
                {
                    $retVal[0] = $i;
                    $retVal[1] = $nbElem;
                    return ($retVal);
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

        public function findPlayersToExpulse()
        {
            $vu = $this->voirEtPlus();
            $joueurArray = $this->searchCasePlayersToExpulse($vu);
            if ($joueurArray[1] < 1)
                return (False);
            $this->goToCaseInView($joueurArray[0]);
            $this->command->expulse();
            $this->toutPrendre();
            return (True);
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

        public function toutPrendre()
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

	}
?>
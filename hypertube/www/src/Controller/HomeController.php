<?php

namespace App\Controller;

use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\Routing\Annotation\Route;
use Symfony\Component\HttpFoundation\JsonResponse;
use App\Entity\Video;
use App\Service\SearchTorrentManager;

class HomeController extends AbstractController
{
    /**
     * @Route("/", name="homepage")
     */
    public function indexAction()
    {
    	$entityManager = $this->getDoctrine()->getManager();
    	$entityManager->getRepository(Video::class)->delOld();
    	
    	return $this->render(
            'Home/index.html.twig'
        );
    }
}
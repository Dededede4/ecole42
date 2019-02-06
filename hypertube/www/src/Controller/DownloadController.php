<?php

namespace App\Controller;

use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\Routing\Annotation\Route;
use Symfony\Component\HttpFoundation\JsonResponse;
use Symfony\Component\HttpFoundation\Response;
use Symfony\Component\HttpFoundation\RedirectResponse;
use Symfony\Component\HttpFoundation\BinaryFileResponse;
use Symfony\Component\HttpFoundation\File\Stream;

use App\Component\InfiniteBinaryFileResponse;

use Sensio\Bundle\FrameworkExtraBundle\Configuration\Security;
use Symfony\Component\HttpFoundation\Request;

use App\Service\SearchTorrentManager;

use App\Service\TorrentManager;

use App\Entity\Video;
use App\Entity\Comment;

use App\Form\CommentType;




class DownloadController extends AbstractController
{
    /**
     * @Route("/stream/{video}", name="stream")
     * @Security("is_granted('ROLE_USER')")
     */
    public function downloadAction(Video $video, TorrentManager $manager)
    {
        
        if (false == $video->getProcessStarted())
        {
            $manager->download($video);

            $video->setProcessStarted(true);
            
            
        }
        $video->setLastSeeAt(new \DateTime());
        $entityManager = $this->getDoctrine()->getManager();
        $entityManager->persist($video);
        $entityManager->flush();
        return $this->redirectToRoute('streamloops', ['video' => $video->getBtih()]);
    }

    /**
     * @Route("/stream/loops/{video}", name="streamloops")
     * @Security("is_granted('ROLE_USER')")
     */
    public function downloadLoopAction(Video $video)
    {
        
        $i = 0;
        while(1)
        {
            $i++;
            $video = $this->getDoctrine()->getManager()->getRepository(Video::class)->find($video->getBtih());;

            if ($video->getDownloadable())
            {
                $stream  = new Stream('/var/www/public/download/stream/'.$video->getBtih().'.mp4');
                return new InfiniteBinaryFileResponse($stream);
            }
            sleep(2);
            if ($i === 10)
            {
                return $this->redirectToRoute('stream', ['video' => $video->getBtih()]);
            }
        }
    }


    /**
     * @Route("/panel/{video}", name="panel")
     * @Security("is_granted('ROLE_USER')")
     */
    public function panelAction(Video $video, Request $request)
    {
    	$comment = new Comment();
    	$form = $this->createForm(CommentType::class, $comment);

        $form->handleRequest($request);
        if ($form->isSubmitted() && $form->isValid()) {
        	$comment
        		->setUser($this->getUser())
        		->setCreatedAt(new \DateTime())
        		->setVideo($video)
        		;
        	$entityManager = $this->getDoctrine()->getManager();
            $entityManager->persist($comment);
            $entityManager->flush();

            return $this->redirectToRoute('panel', ['video' => $video->getBtih()]);
        }
    	

    	return $this->render(
            'Download/panel.html.twig',
            ['video' => $video, 'form' => $form->createView()]
        );
    }


}
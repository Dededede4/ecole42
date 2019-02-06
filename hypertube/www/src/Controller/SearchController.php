<?php

namespace App\Controller;

use App\Entity\Comment;
use App\Entity\User;
use App\Entity\Video;
use App\Entity\Search;
use App\Form\SearchEngineType;
use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\Routing\Annotation\Route;
use Symfony\Component\HttpFoundation\JsonResponse;
use Sensio\Bundle\FrameworkExtraBundle\Configuration\Security;
use Symfony\Component\HttpFoundation\Request;
use App\Service\SearchTorrentManager;

class SearchController extends AbstractController
{
    private $searchTorrentManager;

    public function __construct(SearchTorrentManager $manager)
    {
        $this->searchTorrentManager = $manager;
    }

    /**
     * @Route("/search/{query}.json", name="search_json")
     * @Security("is_granted('ROLE_USER')")
     */
    public function searchJsonAction($query)
    {
        $returnValues = [];

        $videos = $this->searchAndFlush($query);

        foreach ($videos as $video) {
            $selectedValues = [
                'title' => $video->getTitle(),
                'btih' => $video->getBtih(),
            ];
            $returnValues[] = $selectedValues;
        }
        return new JsonResponse($returnValues);
    }

    /**
     * @Route("/search/", name="search")
     * @Security("is_granted('ROLE_USER')")
     */
    public function searchAction(Request $request)
    {
        $search = new Search();
        $form = $this->createForm(SearchEngineType::class, $search, [
            'action' => $this->generateUrl('search'),
            'method' => 'GET',
            'csrf_protection' => false,
        ]);

        $form->handleRequest($request);
        
        if ($form->isSubmitted() && $form->isValid()) {
            
            if($request->isXmlHttpRequest())
            {
                $page = $request->get('page');
                if (!ctype_digit($page))
                    $page = 0;
                $videos = $this->searchAndFlush($search, $page);
                return $this->render(
                'Search/results.html.twig',
                ['videos' => $videos, 'form' => $form->createView()]);
            }
        }

        return $this->render(
            'Search/index.html.twig',
            ['videos' => [], 'form' => $form->createView()]
        );
    }

    private function searchAndFlush($query, $page)
    {
        $videos = $this->searchTorrentManager->search($query, $page);

        $persistedVideos = [];

        $entityManager = $this->getDoctrine()->getManager();
        foreach ($videos as $video) {
            
            $videoBdd = $this->getDoctrine()
            ->getRepository(Video::class)
            ->find($video->getBtih());

            if ($videoBdd)
            {
                $persistedVideos[] = $videoBdd;
            }
            else
            {
                $entityManager->persist($video);
                $persistedVideos[] = $video;
            }
            
            
        }
        $entityManager->flush();

        return $persistedVideos;
    }


    /**
     * @Route("/movies/", name="movies")
     * @Security("is_granted('ROLE_USER')")
     */
    public function moviesAction(Request $request)
    {
        $videos = $this->getDoctrine()
            ->getRepository(Video::class)
            ->findAll();

        return $this->render(
            'Search/index.html.twig',
            ['videos' => $videos]
        );
    }

    /**
     * @Route("/comments/", name="comments")
     * @Security("is_granted('ROLE_USER')")
     */
    public function commentsAction(Request $request)
    {
        $comments = $this->getDoctrine()
            ->getRepository(Comment::class)
            ->findAll();

        return $this->render(
            'Search/comments.html.twig',
            ['comments' => $comments]
        );
    }

    /**
     * @Route("/user/{id}", name="user")
     * @Security("is_granted('ROLE_USER')")
     */
    public function userAction(User $user, Request $request)
    {
        return $this->render(
            'Search/user.html.twig',
            ['user' => $user]
        );
    }
}
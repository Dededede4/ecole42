<?php
namespace App\Controller;

use KnpU\OAuth2ClientBundle\Client\ClientRegistry;
use League\OAuth2\Client\Provider\Exception\IdentityProviderException;
use Symfony\Bundle\FrameworkBundle\Controller\Controller;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\Routing\Annotation\Route;
use Symfony\Component\Security\Core\Authentication\Token\UsernamePasswordToken;
use Symfony\Component\Security\Http\Event\InteractiveLoginEvent;
use Symfony\Component\HttpFoundation\RedirectResponse;

class OAuthController extends Controller
{
    /**
     * Link to this controller to start the "connect" process
     *
     * @Route("/connect/facebook", name="connect_facebook_start")
     */
    public function connectAction(ClientRegistry $clientRegistry)
    {
        // on Symfony 3.3 or lower, $clientRegistry = $this->get('knpu.oauth2.registry');
    
        // will redirect to Facebook!
        return $clientRegistry
            ->getClient('facebook_main') // key used in config/packages/knpu_oauth2_client.yaml
            ->redirect([
	    	'public_profile', 'email' // the scopes you want to access
            ])
        ;
	}

    /**
     * Link to this controller to start the "connect" process
     *
     * @Route("/connect/intra42", name="connect_intra42_start")
     */
    public function connectIntra42Action(ClientRegistry $clientRegistry)
    {
        // on Symfony 3.3 or lower, $clientRegistry = $this->get('knpu.oauth2.registry');
    
        // will redirect to Facebook!
        return $clientRegistry
            ->getClient('intra42') // key used in config/packages/knpu_oauth2_client.yaml
            ->redirect([
            'public' // the scopes you want to access
            ])
        ;
    }


    /**
     * After going to Facebook, you're redirected back here
     * because this is the "redirect_route" you configured
     * in config/packages/knpu_oauth2_client.yaml
     *
     * @Route("/connect/facebook/check", name="connect_facebook_check")
     */
    public function connectCheckAction(Request $request, ClientRegistry $clientRegistry)
    {
        // ** if you want to *authenticate* the user, then
        // leave this method blank and create a Guard authenticator
        // (read below)

        /** @var \KnpU\OAuth2ClientBundle\Client\Provider\FacebookClient $client */
        $client = $clientRegistry->getClient('facebook_main');

        try {
            // the exact class depends on which provider you're using
            /** @var \League\OAuth2\Client\Provider\FacebookUser $user */
            $facebookUser = $client->fetchUser();

            $user = $this->getDoctrine()->getManager()->getRepository("App\Entity\User")->findOneBy(array('facebookId' => $facebookUser->getId()));

            if(null == $user)
            {
                $user = $this->register($facebookUser->getEmail(), $facebookUser->getId(), $facebookUser->getFirstName(), $facebookUser->getLastName());
            }
            $this->connect($request, $user);
            return new RedirectResponse($this->generateUrl('homepage'));
        } catch (IdentityProviderException $e) {
            // something went wrong!
            // probably you should return the reason to the user
            var_dump($e->getMessage()); die;
        }
    }

    /**
     * @Route("/connect/intra42/check", name="connect_intra42_check")
     */
    public function connectCheckIntra42Action(Request $request, ClientRegistry $clientRegistry)
    {
        // ** if you want to *authenticate* the user, then
        // leave this method blank and create a Guard authenticator
        // (read below)

        /** @var \KnpU\OAuth2ClientBundle\Client\Provider\FacebookClient $client */
        $client = $clientRegistry->getClient('intra42');

        try {
            // the exact class depends on which provider you're using
            /** @var \League\OAuth2\Client\Provider\FacebookUser $user */
            $intraUser = $client->fetchUser();
            $user = $this->getDoctrine()->getManager()->getRepository("App\Entity\User")->findOneBy(array('intra42Id' => $intraUser['id']));

            if(null == $user)
            {
                $user = $this->register($intraUser['email'], $intraUser['id'], $intraUser['first_name'], $intraUser['last_name']);
            }
            $this->connect($request, $user);
            return new RedirectResponse($this->generateUrl('homepage'));
        } catch (IdentityProviderException $e) {
            // something went wrong!
            // probably you should return the reason to the user
            var_dump($e->getMessage()); die;
        }
    }

    private function register($email, $fbid, $firstName, $lastName){    
        $userManager = $this->get('fos_user.user_manager');

        // Or you can use the doctrine entity manager if you want instead the fosuser manager
        // to find 
        //$em = $this->getDoctrine()->getManager();
        //$usersRepository = $em->getRepository("mybundleuserBundle:User");
        // or use directly the namespace and the name of the class 
        // $usersRepository = $em->getRepository("mybundle\userBundle\Entity\User");
        //$email_exist = $usersRepository->findOneBy(array('email' => $email));

        $email_exist = $userManager->findUserByEmail($email);

        // Check if the user exists to prevent Integrity constraint violation error in the insertion
        if($email_exist){
          $user = $email_exist;
        }
        else
        {
            $user = $userManager->createUser();
        }
        $user->setUsername($email);
        $user->setEmail($email);
        $user->setEmailCanonical($email);
        $user->setEnabled(1); // enable the user or enable it later with a confirmation token in the email
        // this method will encrypt the password with the default settings :)
        $user->setFacebookId($fbid);
        $user->setPlainPassword('aunisteaunsiteaunristea');
        $user->setFirstName($firstName);
        $user->setLastName($lastName);
        $userManager->updateUser($user);

        return $user;
   }

   private function connect($request, $user)
   {
       
        //Handle getting or creating the user entity likely with a posted form
        // The third parameter "main" can change according to the name of your firewall in security.yml
        $token = new UsernamePasswordToken($user, null, 'main', $user->getRoles());
        $this->get('security.token_storage')->setToken($token);

        // If the firewall name is not main, then the set value would be instead:
        // $this->get('session')->set('_security_XXXFIREWALLNAMEXXX', serialize($token));
        $this->get('session')->set('_security_main', serialize($token));
        
        // Fire the login event manually
        $event = new InteractiveLoginEvent($request, $token);
        $this->get("event_dispatcher")->dispatch("security.interactive_login", $event);
   }
}
<?php

namespace App\Provider;

use League\OAuth2\Client\Provider\AbstractProvider;
use League\OAuth2\Client\Token\AccessToken;
use League\OAuth2\Client\Tool\BearerAuthorizationTrait;
use League\OAuth2\Client\Provider\Exception\IdentityProviderException;
use Psr\Http\Message\ResponseInterface;

class Intra42 extends AbstractProvider
{
    use BearerAuthorizationTrait;

    protected function domain()
    {
        return 'https://api.intra.42.fr';
    }

    public function getBaseAuthorizationUrl()
    {
        return $this->domain() . '/oauth/authorize';
    }

    public function getBaseAccessTokenUrl(array $params = [])
    {
        return $this->domain() . '/oauth/token';
    }

    public function getResourceOwnerDetailsUrl(AccessToken $token)
    {
        return $this->domain() . '/v2/me';
    }

    public function getDefaultScopes()
    {
        return ['public'];
    }

    protected function checkResponse(ResponseInterface $response, $data)
    {
        if ($response->getStatusCode() >= 400) {
            return new IdentityProviderException(
                $response->getReasonPhrase(),
                $response->getStatusCode(),
                $response
            );
        }
    }

    protected function createResourceOwner(array $response, AccessToken $token)
    {
    	return $response; // :d
    }
}
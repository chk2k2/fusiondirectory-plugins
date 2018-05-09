<?php
/*
					COPYRIGHT

Copyright 2007 Sergio Vaccaro <sergio@inservibile.org>
Copyright 2013-2018 FusionDirectory

This file is part of JSON-RPC PHP.

JSON-RPC PHP is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

JSON-RPC PHP is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with JSON-RPC PHP; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

/**
 * This class build a json-RPC Server 1.0
 * http://json-rpc.org/wiki/specification
 *
 * @author sergio <jsonrpcphp@inservibile.org>
 */
class jsonRPCServer {
	/**
	 * This function handle a request binding it to a given object
	 *
	 * @param object $object
	 * @return boolean
	 */
	public static function handle($object) {

		// checks if a JSON-RCP request has been received
		if (
			$_SERVER['REQUEST_METHOD'] != 'POST' ||
			empty($_SERVER['CONTENT_TYPE']) ||
			$_SERVER['CONTENT_TYPE'] != 'application/json'
			) {
			// This is not a JSON-RPC request
			return false;
		}

		// reads the input data
		$request = json_decode(file_get_contents('php://input'),true);

		// executes the task on local object
		try {
			if (($result = @call_user_func_array(array($object,$request['method']),$request['params'])) !== FALSE) {
				$response = array (
									'id' => $request['id'],
									'result' => $result,
									'error' => NULL
									);
			} else {
				$response = array (
									'id' => $request['id'],
									'result' => NULL,
									'error' => 'unknown method or incorrect parameters'
									);
			}
		} catch (Exception $e) {
			$response = array (
								'id' => $request['id'],
								'result' => NULL,
								'error' => $e->getMessage()
								);
		}

		// output the response
    // notifications don't want response
		if (!empty($request['id'])) {
			header('content-type: text/javascript');
			$res = json_encode($response);
			if ($res === FALSE) {
				$response = array (
					'id' => $request['id'],
					'result' => NULL,
					'error' => 'Failed to encode response: '.json_last_error_msg()
				);
				echo json_encode($response);
			} else {
				echo $res;
			}
		}

		// finish
		return true;
	}
}
?>

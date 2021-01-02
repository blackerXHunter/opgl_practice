Shader "Custom/ForwardRendering" {
	Properties {
		_Diffuse("Diffuse", Color) = (1, 1, 1, 1)
		_Specular("Specual", Color) = (1, 1, 1, 1)
		_Gloss("Gloss", Range(8.0, 256)) = 20
	}
	SubShader {
		Tags { "RenderType"="Opaque" }
		Pass {
			Tags {"LightMode"="ForwardBase"}

			CGPROGRAM 
			#pragma multi_compile_fwdbase
			#pragma vertex vert
			#pragma	fragment frag
			#include "Lighting.cginc"
			fixed4 _Diffuse;
			fixed4 _Specular;
			float _Gloss;

			struct a2v {
				float4 vertex :POSITION;
				float3 normal :NORMAL;
			};

			struct v2f {
				float4 pos : SV_POSITION;
				fixed3 worldNormal : TEXCOORD0;
				fixed3 worldPos : TEXCOORD1;
			};

			v2f vert(a2v v) {
				v2f o;
				
				o.pos = UnityObjectToClipPos(v.vertex);
				o.worldNormal = mul(v.normal, (float3x3)unity_WorldToObject);
				o.worldPos = mul(unity_ObjectToWorld, v.vertex).xyz;
				return o;
			}
			fixed4 frag(v2f i) :SV_Target{
				fixed3 ambient = UNITY_LIGHTMODEL_AMBIENT.xyz;

				fixed3 worldNormal = normalize(i.worldNormal);
				fixed3 worldLightDir = normalize(_WorldSpaceLightPos0.xyz);

				fixed3 diffuse = _LightColor0.rbg * _Diffuse.rgb * max(0, dot(worldNormal, worldLightDir));

				//fixed3 reflectDir = normalize(reflect(-worldLightDir, worldNormal));
				fixed3 viewDir = normalize(_WorldSpaceCameraPos.xyz - i.worldPos.xyz);
				fixed3 halfDir = normalize(worldLightDir + viewDir);

				fixed3 specular = _LightColor0.rgb * _Specular.rgb * pow(saturate(dot(halfDir, worldNormal)), _Gloss);
				fixed atten = 1.0;
				return fixed4(ambient + (diffuse + specular)*atten, 1.0);
			}


			ENDCG
		}

		Pass{
			Tags {"LightMode"="ForwardAdd"}
			Blend One One

			CGPROGRAM
			#pragma multi_compile_fwdadd

			#pragma vertex vert
			#pragma	fragment frag
			#include "Lighting.cginc"
			#include "Autolight.cginc"
			fixed4 _Diffuse;
			fixed4 _Specular;
			float _Gloss;

			struct a2v {
				float4 vertex :POSITION;
				float3 normal :NORMAL;
			};

			struct v2f {
				float4 pos : SV_POSITION;
				fixed3 worldNormal : TEXCOORD0;
				fixed3 worldPos : TEXCOORD1;
			};

			v2f vert(a2v v) {
				v2f o;
				
				o.pos = UnityObjectToClipPos(v.vertex);
				o.worldNormal = mul(v.normal, (float3x3)unity_WorldToObject);
				o.worldPos = mul(unity_ObjectToWorld, v.vertex).xyz;
				return o;
			}
			fixed4 frag(v2f i) :SV_Target{
				fixed3 ambient = UNITY_LIGHTMODEL_AMBIENT.xyz;

				fixed3 worldNormal = normalize(i.worldNormal);

				#ifdef USING_DIRECTIONAL_LIGHT
					fixed3 worldLightDir = normalize(_WorldSpaceLightPos0.xyz);
				#else
					fixed3 worldLightDir = normalize(_WorldSpaceLightPos0.xyz-i.worldPos.xyz);
				#endif

				#ifdef USING_DIRECTIONAL_LIGHT
					fixed3 atten = 1.0;
				#else 
					float3 lightCoord = mul(unity_WorldToLight, i.worldPos);
					fixed3 atten = tex2D(_LightTexture0, dot(lightCoord, lightCoord).rr).UNITY_ATTEN_CHANNEL;
				#endif
				

				fixed3 diffuse = _LightColor0.rbg * _Diffuse.rgb * max(0, dot(worldNormal, worldLightDir));

				//fixed3 reflectDir = normalize(reflect(-worldLightDir, worldNormal));
				fixed3 viewDir = normalize(_WorldSpaceCameraPos.xyz - i.worldPos.xyz);
				fixed3 halfDir = normalize(worldLightDir + viewDir);

				fixed3 specular = _LightColor0.rgb * _Specular.rgb * pow(saturate(dot(halfDir, worldNormal)), _Gloss);
				return fixed4((diffuse + specular)*atten, 1.0);
			}
			ENDCG
		}
	}
	FallBack "Specular"
}

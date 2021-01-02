// Upgrade NOTE: replaced '_Object2World' with 'unity_ObjectToWorld'
// Upgrade NOTE: replaced 'mul(UNITY_MATRIX_MVP,*)' with 'UnityObjectToClipPos(*)'

Shader "Custom/AlphaBlend" {
	Properties {
		_Color ("Color", Color) = (1,1,1,1)
		_MainTex ("Albedo (RGB)", 2D) = "white" {}
		_AlphaScale("Alpha Sclae", Range(0,1)) = 1
	}
	SubShader {
		Tags { "Queue"="Transparent" "IgnoreProjector"="true" "RenderType"="Transparent" }
		
		Pass{
			Tags {"LightMode"="ForwardBase"}
			Cull Front
			ZWrite Off
			Blend SrcAlpha OneMinusSrcAlpha
			CGPROGRAM

			#pragma vertex vert
			#pragma fragment frag

			#include "Lighting.cginc"

			sampler2D _MainTex;
			float4 _MainTex_ST;
			fixed4 _Color;
			fixed _AlphaScale;

			struct a2v {
				float4 vertex : POSITION;
				float3 normal : NORMAL;
				float4 texcoord : TEXCOORD;
			};

			struct v2f {
				float4 pos : SV_POSITION;
				float3 worldNormal : TEXCOORD0;
				float3 worldPos : TEXCOORD1;
				float2 uv : TEXCOORD2;
			};
			
			v2f vert(a2v i){
				v2f o;
				o.pos = UnityObjectToClipPos(i.vertex);

				o.worldNormal = UnityObjectToWorldNormal(i.normal);

				o.worldPos = mul(unity_ObjectToWorld, i.vertex).xyz;

				o.uv = TRANSFORM_TEX(i.texcoord, _MainTex);
				return o;
			}

			fixed4 frag(v2f i) : SV_Target{
				fixed3 worldNormal = normalize(i.worldNormal);
				fixed3 worldLightDir = normalize(UnityWorldSpaceLightDir(i.worldPos));

				fixed4 texColor = tex2D(_MainTex, i.uv);

				fixed3 albedo = texColor.rgb * _Color.rgb;

				fixed3 ambient = UNITY_LIGHTMODEL_AMBIENT.xyz * albedo;

				fixed3 diffuse = _LightColor0.rgb * albedo * max(0, dot(worldNormal, worldLightDir));

				return fixed4(ambient + diffuse, texColor.a * _AlphaScale);
			}

			ENDCG
		}

		Pass{
			Tags {"LightMode"="ForwardBase"}
			Cull Back			
			ZWrite Off
			Blend SrcAlpha OneMinusSrcAlpha
			CGPROGRAM

			#pragma vertex vert
			#pragma fragment frag

			#include "Lighting.cginc"

			sampler2D _MainTex;
			float4 _MainTex_ST;
			fixed4 _Color;
			fixed _AlphaScale;

			struct a2v {
				float4 vertex : POSITION;
				float3 normal : NORMAL;
				float4 texcoord : TEXCOORD;
			};

			struct v2f {
				float4 pos : SV_POSITION;
				float3 worldNormal : TEXCOORD0;
				float3 worldPos : TEXCOORD1;
				float2 uv : TEXCOORD2;
			};
			
			v2f vert(a2v i){
				v2f o;
				o.pos = UnityObjectToClipPos(i.vertex);

				o.worldNormal = UnityObjectToWorldNormal(i.normal);

				o.worldPos = mul(unity_ObjectToWorld, i.vertex).xyz;

				o.uv = TRANSFORM_TEX(i.texcoord, _MainTex);
				return o;
			}

			fixed4 frag(v2f i) : SV_Target{
				fixed3 worldNormal = normalize(i.worldNormal);
				fixed3 worldLightDir = normalize(UnityWorldSpaceLightDir(i.worldPos));

				fixed4 texColor = tex2D(_MainTex, i.uv);

				fixed3 albedo = texColor.rgb * _Color.rgb;

				fixed3 ambient = UNITY_LIGHTMODEL_AMBIENT.xyz * albedo;

				fixed3 diffuse = _LightColor0.rgb * albedo * max(0, dot(worldNormal, worldLightDir));

				return fixed4(ambient + diffuse, texColor.a * _AlphaScale);
			}

			ENDCG
		}


	}
	FallBack "Transparent/VertexLit"
}
